#include "flist_global.h"
#include <QApplication>
#include <QByteArray>
#include <iostream>
#include "flist_parser.h"
#include "api/endpoint_v1.h"

QNetworkAccessManager *networkaccessmanager = 0;
BBCodeParser *bbcodeparser = 0;
FHttpApi::Endpoint *fapi = 0;

void debugMessage(QString str) {
	std::cout << str.toUtf8().data() << std::endl;
}

void debugMessage(std::string str) {
	std::cout << str << std::endl;
}

void debugMessage(const char *str) {
	std::cout << str << std::endl;
}

void globalInit()
{
	networkaccessmanager = new QNetworkAccessManager(qApp);
	bbcodeparser = new BBCodeParser();
	fapi = new FHttpApi::Endpoint_v1(networkaccessmanager);
}

void globalQuit()
{

}



bool is_broken_escaped_apos(std::string const &data, std::string::size_type n)
{
        return n + 2 <= data.size()
                        and data[n] == '\\'
                        and data[n+1] == '\'';
}
void fix_broken_escaped_apos (std::string &data)
{
        for ( std::string::size_type n = 0; n != data.size(); ++n )
        {
                if ( is_broken_escaped_apos ( data, n ) )
                {
                        data.replace ( n, 2, 1, '\'' );
                }
        }
}

QString escapeFileName(QString infilename)
{
	QByteArray inname(infilename.toUtf8());
	QByteArray outname;
	for(int i = 0; i < inname.length(); i++) {
		unsigned char c = inname.at(i);
		if((c >= 'A' && c <= 'Z') ||
		   (c >= 'a' && c <= 'z') ||
		   (c >= '0' && c <= '9') ||
		   c == '-' ||
		   c == '_' ||
		   c == ' ' ||
		   c == '.') {
			outname.append(c);
		} else {
			outname.append('%');
			outname.append(QByteArray::number(c, 16));
		}
	}
	return QString::fromUtf8(outname);
}
