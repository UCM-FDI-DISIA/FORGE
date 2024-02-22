// Este archivo es para que se suba la carpeta src/Render a Github
#include <OgreException.h>
#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include "OgreTextureManager.h"
#include "OgreRenderWindow.h"
class TutorialApplication
{
    private:
        Ogre::Root* mRoot;
        Ogre::String mResourcesCfg;
        Ogre::String mPluginsCfg;
    public:
    TutorialApplication(): mRoot(0), mResourcesCfg(Ogre::BLANKSTRING),mPluginsCfg(Ogre::BLANKSTRING)
    {
    }
    
    virtual ~TutorialApplication()
    {
        delete mRoot;
    }
    
    bool go()
    {
#ifdef _DEBUG
        mResourcesCfg = "resources_d.cfg";
        mPluginsCfg = "plugins_d.cfg";
#else
        mResourcesCfg = "resources.cfg";
        mPluginsCfg = "plugins.cfg";
#endif

        mRoot = new Ogre::Root(mPluginsCfg);

        Ogre::ConfigFile cf;
        cf.load(mResourcesCfg);

        Ogre::String name, locType;
        auto secIt = cf.getSettingsBySection().begin();

        while (secIt!= cf.getSettingsBySection().end())
        {
            auto settings = (*secIt).second;
            Ogre::ConfigFile::SettingsMultiMap::iterator it;

            for (it = settings.begin(); it != settings.end(); ++it)
            {
                locType = it->first;
                name = it->second;

                Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, locType);
            }
            secIt++;
        }

        Ogre::RenderWindow* mWindow;
        if (!(mRoot->restoreConfig() || mRoot->showConfigDialog(nullptr))) return false;

        mWindow = mRoot->initialise(true, "TutorialApplication Render Window");
        Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
        Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

        return true;
    }
   
    
};




int main()
{
    TutorialApplication hola;
    hola.go();
    return 0;
}