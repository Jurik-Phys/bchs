#include "appWindow.h"
#include "microtex.h"

void initQt() {
    microtex::PlatformFactory::registerFactory(
        "qt",
        std::make_unique<microtex::PlatformFactory_qt>()
      );
      microtex::PlatformFactory::activate("qt");
}

int main(int argc, char** argv){

    QApplication app(argc, argv);

    // Use this fonts file for draw formula
    // copy file from "ext/MicroTeX/res/firamath"
    const char* fontClmFile = "FiraMath-Regular.clm2";
    const char* fontOtfFile = "FiraMath-Regular.otf";

    const microtex::FontSrcFile math{fontClmFile, fontOtfFile};
    microtex::MicroTeX::init(math);

    initQt();

    QAppWindow appWindow;
    appWindow.show();
    int retn = app.exec();

    microtex::MicroTeX::release();
    return retn;
}
