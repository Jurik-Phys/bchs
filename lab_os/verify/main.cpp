#include "appWindow.h"
#include "microtex.h"

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

    QApplication app(argc, argv);
    QIcon appIcon(":res/icon.png");

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
