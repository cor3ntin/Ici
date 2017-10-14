import qbs

AnkamaDynamicLibrary {
    name:"ici"

    Depends { name: "cpp" }

    Depends { name: "flex" }
    Depends { name: "qlalr" }
    Depends { name: "Qt.core" }


    cpp.includePaths: [
        "src",
    ]
    cpp.defines : ["ICI_EXPORT_DLL"]

    Group {
        name : "Sources"
        files: [
            "*.cpp",
            "*.h",
            "*.l",
            "*.g"
        ]
        prefix: "src/**/"
    }

    Export {
        Depends { name: "cpp" }
        Depends { name: "Qt.core" }
        cpp.includePaths: "src"
        cpp.defines : ["ICI_IMPORT_DLL"]
    }
}
