#include <QApplication>
#include <QDir>
#include <iostream>

struct Context
{
	QString filename;
	QString path;
	int parentID;
	int currentID;
};
//---------------------

class eventFiles
{
	public:
		virtual Context onFile(const Context&) = 0;
		virtual Context onEnterDir(const Context&) = 0;
		virtual Context onLeavedDir(const Context&) = 0;
};

//---------------------

void getDirFiles( const QString& dirName, eventFiles & events)
{
	Context ctxDir;
	ctxDir.filename = dirName;
	ctxDir.path = "";
	ctxDir = events.onEnterDir(ctxDir);

	QDir dir( dirName );
	QStringList fileList = dir.entryList( QDir::Files );

	for(int i = 0; i < fileList.size(); i++)
	{
		Context ctx;
		ctx.filename = fileList.at(i);
		ctx.path = ;
		events.onFile(ctx);
	}

	QStringList dirList = dir.entryList( QDir::Dirs );

	for(int i = 0; i < dirList.size(); i++)
	{
		QString dir = dirName + "/" + dirList.at(i);
		if(dirList.at(i) != "." && dirList.at(i) != "..")
		{
			
			getDirFiles(dir, events);
		}
	}

	events.onLeavedDir(ctxDir);
	return;
}

// ----------

class myEvents : public eventFiles
{
	public:
		virtual Context onFile(const Context &ctx) 
		{
			
//			QString filename;
//			QString path;

			std::cout << ctx.filename.toStdString() << "\n";
			return Context();	
		};
		virtual Context onEnterDir(const Context &ctx) 
		{
			return Context();
		};
		virtual Context onLeavedDir(const Context &ctx) 
		{
			return Context();
		};
};

// ----------

int main()
{
	myEvents evns;	
	getDirFiles(".", evns);

	return 0;
}
