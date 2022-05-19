cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 11)

add_compile_definitions(
        WIN32
        _WIN32
        NDEBUG
        _LIB
        _CRT_SECURE_NO_DEPRECATE
        _CRT_NONSTDC_NO_DEPRECATE
)

include_directories(
        headers
        ${SE_COMMON}
        ${SE_PUBLIC}
        ${SE_PUBLIC}/tier0
        ${SE_PUBLIC}/tier1
)

add_library(vgui_controls STATIC

        ${SE_PUBLIC}/tier0/memdbgon.h
        ${SE_PUBLIC}/tier1/mempool.h
        ${SE_PUBLIC}/vgui_controls/Menu.h
        ${SE_PUBLIC}/vgui_controls/MenuBar.h
        ${SE_PUBLIC}/vgui_controls/MenuButton.h
        ${SE_PUBLIC}/vgui_controls/MenuItem.h
        ${SE_PUBLIC}/vgui_controls/MessageBox.h
        ${SE_PUBLIC}/vgui_controls/MessageDialog.h
        ${SE_PUBLIC}/vgui_controls/Panel.h
        ${SE_PUBLIC}/vgui_controls/PanelAnimationVar.h
        ${SE_PUBLIC}/vgui_controls/PanelListPanel.h
        ${SE_PUBLIC}/vgui_controls/PerforceFileExplorer.h
        ${SE_PUBLIC}/vgui_controls/PerforceFileList.h
        ${SE_PUBLIC}/vgui_controls/PHandle.h
        ${SE_PUBLIC}/vgui_controls/ProgressBar.h
        ${SE_PUBLIC}/vgui_controls/ProgressBox.h
        ${SE_PUBLIC}/vgui_controls/PropertyDialog.h
        ${SE_PUBLIC}/vgui_controls/PropertyPage.h
        ${SE_PUBLIC}/vgui_controls/PropertySheet.h
        ${SE_PUBLIC}/vgui_controls/QueryBox.h
        ${SE_PUBLIC}/vgui_controls/RadioButton.h
        ${SE_PUBLIC}/vgui_controls/RichText.h
        ${SE_PUBLIC}/vgui_controls/RotatingProgressBar.h
        ${SE_PUBLIC}/vgui_controls/savedocumentquery.h
        ${SE_PUBLIC}/vgui_controls/ScrollableEditablePanel.h
        ${SE_PUBLIC}/vgui_controls/ScrollBar.h
        ${SE_PUBLIC}/vgui_controls/ScrollBarSlider.h
        ${SE_PUBLIC}/vgui_controls/SectionedListPanel.h
        ${SE_PUBLIC}/vgui_controls/Slider.h
        ${SE_PUBLIC}/vgui_controls/Splitter.h
        ${SE_PUBLIC}/vgui_controls/subrectimage.h
        ${SE_PUBLIC}/vgui_controls/TextEntry.h
        ${SE_PUBLIC}/vgui_controls/TextImage.h
        ${SE_PUBLIC}/vgui_controls/ToggleButton.h
        ${SE_PUBLIC}/vgui_controls/Tooltip.h
        ${SE_PUBLIC}/vgui_controls/ToolWindow.h
        ${SE_PUBLIC}/vgui_controls/TreeView.h
        ${SE_PUBLIC}/vgui_controls/TreeViewListControl.h
        ${SE_PUBLIC}/vgui_controls/URLLabel.h
        ${SE_PUBLIC}/tier1/utlmemory.h
        ${SE_PUBLIC}/tier1/utlrbtree.h
        ${SE_PUBLIC}/tier1/utlvector.h
        ${SE_PUBLIC}/vgui_controls/WizardPanel.h
        ${SE_PUBLIC}/vgui_controls/WizardSubPanel.h

        src/AnalogBar.cpp
        src/AnimatingImagePanel.cpp
        src/AnimationController.cpp
        src/BitmapImagePanel.cpp
        src/BuildFactoryHelper.cpp
        src/BuildGroup.cpp
        src/BuildModeDialog.cpp
        src/Button.cpp
        src/CheckButton.cpp
        src/CheckButtonList.cpp
        src/CircularProgressBar.cpp
        src/ComboBox.cpp
        src/consoledialog.cpp
        src/ControllerMap.cpp
        src/controls.cpp
        src/DirectorySelectDialog.cpp
        src/Divider.cpp
        src/EditablePanel.cpp
        src/ExpandButton.cpp
        src/FileOpenDialog.cpp
        src/FileOpenStateMachine.cpp
        src/FocusNavGroup.cpp
        src/Frame.cpp
        src/GraphPanel.cpp
        src/HTML.cpp
        src/Image.cpp
        src/ImageList.cpp
        src/ImagePanel.cpp
        src/InputDialog.cpp
        src/KeyBindingHelpDialog.cpp
        src/KeyBoardEditorDialog.cpp
        src/KeyRepeat.cpp
        src/Label.cpp
        src/ListPanel.cpp
        src/ListViewPanel.cpp
        src/Menu.cpp
        src/MenuBar.cpp
        src/MenuButton.cpp
        src/MenuItem.cpp
        src/MessageBox.cpp
        src/MessageDialog.cpp
        src/Panel.cpp
        src/PanelListPanel.cpp
        src/PerforceFileExplorer.cpp
        src/PerforceFileList.cpp
        src/perforcefilelistframe.cpp
        src/ProgressBar.cpp
        src/ProgressBox.cpp
        src/PropertyDialog.cpp
        src/PropertyPage.cpp
        src/PropertySheet.cpp
        src/QueryBox.cpp
        src/RadioButton.cpp
        src/RichText.cpp
        src/RotatingProgressBar.cpp
        src/savedocumentquery.cpp
        src/ScrollableEditablePanel.cpp
        src/ScrollBar.cpp
        src/ScrollBarSlider.cpp
        src/SectionedListPanel.cpp
        src/Slider.cpp
        src/Splitter.cpp
        src/subrectimage.cpp
        src/TextEntry.cpp
        src/TextImage.cpp
        src/ToggleButton.cpp
        src/Tooltip.cpp
        src/ToolWindow.cpp
        src/TreeView.cpp
        src/TreeViewListControl.cpp
        src/URLLabel.cpp
        src/WizardPanel.cpp
        src/WizardSubPanel.cpp
)

set_property(TARGET vgui_controls PROPERTY
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/public/)

set_property(TARGET vgui_controls PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded")

target_link_options(vgui_controls PRIVATE
        /NODEFAULTLIB:libc
        /NODEFAULTLIB:libcd
        /NODEFAULTLIB:libcmtd
        )
