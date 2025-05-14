#include "appWindow.h"
#include "microtex.h"
#include <iostream>

#ifdef Q_OS_WIN
    #include <windows.h>
#endif

void initQtTeX() {
    // "openmath" rendering quality worse than "master" branch (for Windows)
    // https://github.com/NanoMichael/MicroTeX/issues/159
    microtex::MicroTeX::setRenderGlyphUsePath(true);

    microtex::PlatformFactory::registerFactory("qt",
        std::make_unique<microtex::PlatformFactory_qt>()
    );
    microtex::PlatformFactory::activate("qt");
}

int main(int argc, char** argv){

    #ifdef Q_OS_WIN
	// Console output. Work with MSYS2 terminal
	AttachConsole(ATTACH_PARENT_PROCESS);
    #endif

    QApplication app(argc, argv);
    QIcon appIcon(":/icon.png");

    // Use this fonts file for draw formula
    // copy file from "ext/MicroTeX/res/firamath"
    const char* fontClmFile = "FiraMath-Regular.clm2";
    const char* fontOtfFile = "FiraMath-Regular.otf";

    const microtex::FontSrcFile math{fontClmFile, fontOtfFile};
    microtex::MicroTeX::init(math);

    initQtTeX();

    QAppWindow appWindow;
    appWindow.setWindowIcon(appIcon);
    appWindow.show();
    int retn = app.exec();

    microtex::MicroTeX::release();
    return retn;
}
