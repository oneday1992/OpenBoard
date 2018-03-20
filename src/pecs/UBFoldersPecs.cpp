#include "UBFoldersPecs.h"
#include "globals/UBGlobals.h"

const char *UBFoldersPecs::objNamePathList = "PathList";
const char *UBFoldersPecs::objNameFeatureList = "FeatureList";

UBFoldersPecs::UBFoldersPecs(QWidget *parent, const char *name) : UBDockPaletteWidget(parent)
{
    setObjectName(name);
    mName = "FoldersPecs";
    mVisibleState = true;
    SET_STYLE_SHEET();

    mIconToLeft = QPixmap(":images/library_open.png");
    mIconToRight = QPixmap(":images/library_close.png");
    setAcceptDrops(true);

    //Main UBFeature functionality
    controller = new UBFeaturesController(this);

    //Main layout including all the widgets in palette
    layout = new QVBoxLayout(this);

    //Path icon view on the top of the palette
    pathListView = new UBFeaturesListView(this, objNamePathList);
    controller->assignPathListView(pathListView);

    centralWidget = new UBFeaturesCentralWidget(this);
    //controller->assignFeaturesListView(centralWidget->listView());
    centralWidget->setSliderPosition(UBSettings::settings()->featureSliderPosition->get().toInt());

    //Bottom actionbar for DnD, quick search etc
    mActionBar = new UBFeaturesActionBar(controller, this);

    //Filling main layout
    layout->addWidget(pathListView);
    layout->addWidget(centralWidget);
    layout->addWidget(mActionBar);

}

UBFoldersPecs::~UBFoldersPecs()
{

}
