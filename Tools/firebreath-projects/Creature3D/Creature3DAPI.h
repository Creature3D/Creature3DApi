/**********************************************************\

  Auto-generated Creature3DAPI.h

\**********************************************************/

#include <string>
#include <sstream>
#include <boost/weak_ptr.hpp>
#include "JSAPIAuto.h"
#include "BrowserHost.h"
#include "Creature3D.h"
#include <map>
#include<wininet.h>
#ifndef H_Creature3DAPI
#define H_Creature3DAPI

class Creature3DAPI : public FB::JSAPIAuto
{
public:
    ////////////////////////////////////////////////////////////////////////////
    /// @fn Creature3DAPI::Creature3DAPI(const Creature3DPtr& plugin, const FB::BrowserHostPtr host)
    ///
    /// @brief  Constructor for your JSAPI object.
    ///         You should register your methods, properties, and events
    ///         that should be accessible to Javascript from here.
    ///
    /// @see FB::JSAPIAuto::registerMethod
    /// @see FB::JSAPIAuto::registerProperty
    /// @see FB::JSAPIAuto::registerEvent
    ////////////////////////////////////////////////////////////////////////////
    Creature3DAPI(const Creature3DPtr& plugin, const FB::BrowserHostPtr& host) :
        m_plugin(plugin), m_host(host)
    {
		registerMethod("setParam", make_method(this, &Creature3DAPI::setParam));
		registerMethod("Init", make_method(this, &Creature3DAPI::initialize));

        registerMethod("echo",      make_method(this, &Creature3DAPI::echo));
        //registerMethod("testEvent", make_method(this, &Creature3DAPI::testEvent));
        
        // Read-write property
        //registerProperty("testString",
        //                 make_property(this,
        //                               &Creature3DAPI::get_testString,
        //                               &Creature3DAPI::set_testString));
        
        // Read-only property
        registerProperty("version",
                         make_property(this,
                                       &Creature3DAPI::get_version));
		m_params.clear();
		//versionupdate
		m_shutdown = false;
		m_internetopen = NULL;
		registerMethod("setHost", make_method(this, &Creature3DAPI::setHost));
		registerMethod("versionCheckAndUpdate", make_method(this, &Creature3DAPI::versionCheckAndUpdate));
		registerMethod("getVersionUpdateProgress", make_method(this, &Creature3DAPI::getVersionUpdateProgress));
		registerMethod("getLocalVersion", make_method(this, &Creature3DAPI::getLocalVersion));
		registerMethod("getServerVersion", make_method(this, &Creature3DAPI::getServerVersion));
		///download
		registerMethod("setSavePath", make_method(this, &Creature3DAPI::setSavePath));
		registerMethod("setUnCompressPath", make_method(this, &Creature3DAPI::setUnCompressPath));
		registerMethod("download", make_method(this, &Creature3DAPI::download));
		registerMethod("downloadAndRename", make_method(this, &Creature3DAPI::downloadAndRename));
		registerMethod("getDownloadProgress", make_method(this, &Creature3DAPI::getDownloadProgress));
		registerMethod("isFileExist", make_method(this, &Creature3DAPI::isFileExist));
		registerMethod("deleteFile", make_method(this, &Creature3DAPI::deleteFile));
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @fn Creature3DAPI::~Creature3DAPI()
    ///
    /// @brief  Destructor.  Remember that this object will not be released until
    ///         the browser is done with it; this will almost definitely be after
    ///         the plugin is released.
    ///////////////////////////////////////////////////////////////////////////////
    virtual ~Creature3DAPI() {};

    Creature3DPtr getPlugin();

    // Read/Write property ${PROPERTY.ident}
    //std::string get_testString();
    //void set_testString(const std::string& val);

    // Read-only property ${PROPERTY.ident}
    std::string get_version();

    // Method echo
    FB::variant echo(const FB::variant& msg);
    
    // Event helpers
    //FB_JSAPI_EVENT(test, 0, ());
    FB_JSAPI_EVENT(echo, 2, (const FB::variant&, const int));

    // Method test-event
    //void testEvent();
	void setParam(const std::string& key, const std::string& value);
	std::string getParam(const std::string& key);
	void initialize();
	void StartCreature3D(/*HWND hWndParent, HWND hWnd, int x, int y, int width, int height*/);
	bool WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult);
	void WriteLoginInfo2File(const std::string& logininfo);	//����¼��Ϣд�ļ�
	void shut();
	void exitGame();
	void needRestart();
	void waitClose();
	FB::BrowserHostPtr getHost(){ return m_host; }
	bool copyFile(const std::string &srcFile, const std::string &destFile);
	void initDialog();
	void showDialog(char* url);
	//void gameLog(int value);
	//void download();
	std::string findPath(const std::string &path);
	typedef std::map<std::string, std::string> ParamMap;
	//////////////////versionupdate
	void setHost(const std::string& hostpath);//�磺http://static.duc.cn
	void setSavePath(const std::string& savepath);//�ļ�������ɺ�ı���·���磺DownloadTest
	void setUnCompressPath(const std::string& savepath);//�ļ���ѹ·���磺UnCompressPath
	char download(const std::string& url);//0��������-1������ļ����ǿյģ�-2�ļ��Ѿ����ڣ������ļ���=savepath+"/"+filename������isFileExist(filename)�ж�����-3����������������,-4�Ѿ������أ�-5Internet�쳣
	char downloadAndRename(const std::string& url,std::string filerename="");
	float getDownloadProgress(const std::string& filename);//��ȡ�ļ������ؽ���,����ֵֵ��Ϊ[0.0,1.0]�����ļ��Ѿ����ڣ������ļ���=savepath+"/"+filename������isFileExist(filename)�ж����򷵻�1.0
	char versionCheckAndUpdate(const std::string &url);//1����Ҫ���汾���£�0������Ҫ���汾����
	float getVersionUpdateProgress();//��ȡ�汾���½���
	std::string getLocalVersion();//��ȡ��ǰ�汾��
	std::string getServerVersion();//��ȡ���°汾��
	bool isFileExist(const std::string& filename);//����true:��ʾ���ش��ڸ��ļ���false��ʾ������ �����ļ���=savepath+"/"+filename
	void deleteFile(const std::string& filename);//ɾ�������ļ������ڿ����õ����������ع��� �����ļ���=savepath+"/"+filename
	typedef std::map< std::string,std::pair<float,std::pair<HANDLE,HINTERNET> > >DownloadTaskMap;//filename��threadhandle,����
	void versionUpdate();
	bool versionUpdateCopyFile(const std::string &srcFile, const std::string &destFile);
public:
    Creature3DWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;

    //std::string m_testString;
	ParamMap m_params;
	
	HINTERNET m_internetopenurl;
	std::string m_exename;
	std::string m_clientPath;
	bool m_needRestart;
	HMODULE m_creature3d;
	HMODULE m_dialog;
	HANDLE m_thread;
	//HANDLE m_downloadThread;
	HWND m_hWnd;
	int m_downloadState;
	////////versionupdate
	std::string m_downloadHost;
	std::string m_savepath;
	std::string m_uncompresspath;
	std::string m_disk;
	std::string m_apppath;
	std::string m_dllpath;
	std::string m_currentfile;
	std::string m_localVer;
	std::string m_serverVer;
	DownloadTaskMap m_downloadmap;
	std::deque<HANDLE> m_closeThreadHandleDeque;
	bool m_shutdown;
	HINTERNET m_internetopen;
};

#endif // H_Creature3DAPI

