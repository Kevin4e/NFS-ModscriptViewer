#pragma once

#include <QColor>
#include <QMap>
#include <QString>

struct CommandRule {
    QColor cmdColor;
    QVector<QColor> argColors;

    QVector<QColor> colors() const {
        QVector<QColor> colors;
        colors.reserve(argColors.size() + 1);

        colors.append(cmdColor);
        colors.append(argColors);

        return colors;
    }
};

namespace Attrib {
    // ---- Attribulator v2.0 Instructions Set Formats ---- //

    namespace Cmd {
        // Commands

        const QColor Node{ 0x40FFBA };
        const QColor Field{ 0x69DDFF };
        const QColor Collection{ 0x569CD6 };
        const QColor Overwrite{ 0x95DB7D };
        const QColor ChngVlt{ 0xFF7700 };
        const QColor UI{ 0x8AB4F8 };
        const QColor File{ 0x569CD6 };
        const QColor Folder{ File };
        const QColor Array{ 0x16DF00 };
    }

    namespace Arg {
        // Arguments

        const QColor Class{ 0xFFD700 };
        const QColor Node{ 0xFFFF66 };
        const QColor Field{ 0xFF2836 };
        const QColor SubFields{ 0xDF3079 };
        const QColor Property{ 0xB59F38 };
        const QColor Value{ 0xBEB7FF };
        const QColor String{ 0xD69D85 };
        const QColor UIOption{ 0x00CC00 };
        const QColor Options{ 0xFF50FF };
        const QColor InitialFolderFile{ Arg::Class };
        const QColor DestinationFolderFile{ Arg::Node };
        const QColor Parent{ Class };
        const QColor ParentNode{ Node };
        const QColor NodeName{ String };
        const QColor VaultName{ Node };
        const QColor SourceNode{ Node };
        const QColor TargetNode{ Node };
        const QColor Name{ String };
    }

    const inline QMap<QString, CommandRule> rules {
        { "add_field",         { Cmd::Field,      { Arg::Class, Arg::Node,       Arg::Field                     }}},
        { "add_node",          { Cmd::Node,       { Arg::Class, Arg::ParentNode, Arg::NodeName                  }}},
        { "add_overwrite",     { Cmd::Overwrite,  { Arg::Class, Arg::ParentNode, Arg::NodeName                  }}},
        { "append_array",      { Cmd::Array,      { Arg::Class, Arg::Node,       Arg::Field,      Arg::Value    }}},
        { "change_vault",      { Cmd::ChngVlt,    { Arg::Class, Arg::Node,       Arg::VaultName                 }}},
        { "copy_fields",       { Cmd::Field,      { Arg::Class, Arg::SourceNode, Arg::TargetNode, Arg::Options  }}},
        { "copy_node",         { Cmd::Node,       { Arg::Class, Arg::SourceNode, Arg::ParentNode, Arg::NodeName }}},
        { "copy_overwrite",    { Cmd::Overwrite,  { Arg::Class, Arg::SourceNode, Arg::ParentNode, Arg::NodeName }}},
        { "delete_field",      { Cmd::Field,      { Arg::Class, Arg::Node,       Arg::Field                     }}},
        { "delete_node",       { Cmd::Node,       { Arg::Class, Arg::Node                                       }}},
        { "move_node",         { Cmd::Node,       { Arg::Class, Arg::Node,       Arg::Parent                    }}},
        { "rename_node",       { Cmd::Node,       { Arg::Class, Arg::Node,       Arg::Name                      }}},
        { "resize_field",      { Cmd::Field,      { Arg::Class, Arg::Node,       Arg::Field,      Arg::Value    }}},
        { "update_collection", { Cmd::Collection, { Arg::Class, Arg::Node,       Arg::Field                     }}},

        { "ui_text",           { Cmd::UI,         { Arg::String                                                 }}},
        { "ui_control",        { Cmd::UI,         {                                                             }}},
        { "ui_option",         { Cmd::UI,         { Arg::UIOption                                               }}},
        { "folder_create",     { Cmd::Folder,     { Arg::InitialFolderFile                                      }}},
        { "file_copy",         { Cmd::Folder,     { Arg::InitialFolderFile,  Arg::DestinationFolderFile         }}}
    };
}

namespace Bin {
    // ---- Binary Instructions Set Formats ---- //

    namespace Cmd {
        // Commands
        const QColor InputControls{};
        const QColor Collection{ 0x66ADD8 };
        const QColor InCareer{ 0xEA66BA };
        const QColor String{ 0xC699E3 };
        const QColor Texture{ 0x00E5FF };
        const QColor Statements{ 0x66FFFF }; // append, delete, else, end, if, import, new, static
        const QColor File{ Attrib::Cmd::File };
        const QColor Folder{ Attrib::Cmd::Folder };
        const QColor Stream{ 0x5D7711 };
        const QColor UIOption{ 0x661188 };
    }

    namespace Arg {
        // Arguments

        const QColor File{ 0xAEEA00 };
        const QColor Folder{ 0xFFF59D };
        const QColor Manager{ 0x7C4DFF };
        const QColor Collection;
        const QColor TPKBlock{ 0xFF4081 };
        const QColor Type{ 0xFFB300 };
        const QColor FilePath{ 0xFFFF66 };
        const QColor String{ 0xD69D85 };

        const QColor FileName{ File };
        const QColor GCareer{ 0x8AB4F8 };
        const QColor Root{ 0xCC6600 };
        const QColor STRBlock{ TPKBlock };
        const QColor TexPath{ String };

        const QColor From{ String };
        const QColor To{ String };

        const QColor RelativeAbsolute{ Type };

        const QColor KeyLabel{ 0xCC3399 };
        const QColor DDSPath{ FilePath };

        const QColor Property{ 0x6611000 };
        const QColor Value{ 0x779911 };

        const QColor Text{ String };

        const QColor Endscript{ FilePath };

        const QColor Description{ Text };

        const QColor Condition{ 0x991166 };

        const QColor Boolean{ 0x6C99BB };

        const QColor LXRY{ FilePath };
        const QColor STREAMLXRY{ FilePath };
        const QColor UnpackPath{ FilePath };

        const QColor DataPath{ FilePath };
    }

    namespace Others {
        const QColor Versn{ 0xFF44FF };
    }

    const inline QMap<QString, CommandRule> rules {
        { "add_collection",         { Cmd::Collection, { Arg::FileName,         Arg::Manager,          Arg::Collection                                                                    }}},
        { "add_incareer",           { Cmd::InCareer,   { Arg::FileName,         Arg::Manager,          Arg::GCareer,          Arg::Root,       Arg::Collection                            }}},
        { "add_or_replace_texture", {                  {                                                                                                                                  }}},
        { "add_or_update_string",   {                  {                                                                                                                                  }}},
        { "add_string",             { Cmd::String,     { Arg::FileName,         Arg::Manager,          Arg::STRBlock,                                                                     }}},
        { "add_texture",            { Cmd::Texture,    { Arg::FileName,         Arg::Manager,          Arg::TPKBlock,         Arg::Collection, Arg::TexPath                               }}},
        { "append",                 { Cmd::Statements, { Arg::Endscript                                                                                                                   }}},
        { "bind_textures",          { Cmd::Texture,    { Arg::Type,             Arg::File,             Arg::Manager,          Arg::TPKBlock,   Arg::Folder                                }}},
        { "checkbox",               { Cmd::UIOption,   { Arg::Description                                                                                                                 }}},
        { "copy_collection",        { Cmd::Collection, { Arg::FileName,         Arg::Manager,          Arg::From,             Arg::To                                                     }}},
        { "copy_incareer",          { Cmd::InCareer,   { Arg::FileName,         Arg::Manager,          Arg::GCareer,          Arg::Root,       Arg::From,       Arg::To                   }}},
        { "copy_texture",           { Cmd::Texture,    { Arg::File,             Arg::Manager,          Arg::TPKBlock,         Arg::From,       Arg::To                                    }}},
        { "create_file",            { Cmd::File,       { Arg::Type,             Arg::RelativeAbsolute, Arg::Folder                                                                        }}},
        { "create_folder",          {                  {                                                                                                                                  }}},
        { "delete",                 { Cmd::Statements, { Arg::FileName                                                                                                                    }}},
        { "erase_file",             { Cmd::File,       { Arg::RelativeAbsolute, Arg::FilePath                                                                                             }}},
        { "erase_folder",           { Cmd::Folder,     { Arg::RelativeAbsolute, Arg::Folder                                                                                               }}},
        { "import",                 { Cmd::Statements, { Arg::Type,             Arg::File,             Arg::Manager,          Arg::String                                                 }}},
        { "if",                     { Cmd::Statements, { Arg::Condition                                                                                                                   }}},
        { "move_file",              { Cmd::File,       { Arg::Type,             Arg::RelativeAbsolute, Arg::RelativeAbsolute, Arg::From,       Arg::To                                    }}},
        { "new",                    { Cmd::Statements, { Arg::Type,             Arg::File                                                                                                 }}},
        { "pack_stream",            { Cmd::Stream,     { Arg::LXRY,             Arg::STREAMLXRY,       Arg::DataPath                                                                      }}},
        { "remove_collection",      { Cmd::Collection, { Arg::File,             Arg::Manager                                                                                              }}},
        { "remove_incareer",        { Cmd::InCareer,   { Arg::File,             Arg::Manager,          Arg::GCareer,          Arg::Root,       Arg::Collection                            }}},
        { "remove_string",          { Cmd::String,     { Arg::File,             Arg::Manager,          Arg::STRBlock,         Arg::KeyLabel                                               }}},
        { "remove_texture",         { Cmd::Texture,    { Arg::File,             Arg::Manager,          Arg::TPKBlock,         Arg::Collection                                             }}},
        { "replace_texture",        { Cmd::Texture,    { Arg::File,             Arg::Manager,          Arg::TPKBlock,         Arg::Collection, Arg::DDSPath                               }}},
        { "static",                 { Cmd::Statements, { Arg::File,             Arg::Manager,          Arg::Property,         Arg::Value                                                  }}},
        { "stop_errors",            { Cmd::Statements, { Arg::Boolean                                                                                                                     }}},
        { "unpack_stream",          { Cmd::Stream,     { Arg::LXRY,             Arg::STREAMLXRY,       Arg::UnpackPath                                                                    }}},
        { "update_collection",      { Cmd::Collection, { Arg::File,             Arg::Manager,          Arg::Collection,       Arg::Property,   Arg::Value                                 }}},
        { "update_incareer",        { Cmd::InCareer,   { Arg::File,             Arg::Manager,          Arg::GCareer,          Arg::Root,       Arg::Collection, Arg::Property, Arg::Value }}},
        { "update_string",          { Cmd::String,     { Arg::File,             Arg::Manager,          Arg::STRBlock,         Arg::KeyLabel,   Arg::Property,   Arg::Value                }}},
        { "update_texture",         { Cmd::Texture,    { Arg::File,             Arg::Manager,          Arg::TPKBlock,         Arg::Collection, Arg::Property,   Arg::Value                }}},
        { "version",                { Cmd::Statements, { Arg::Value                                                                                                                       }}},
        { "watermark",              { Cmd::Statements, { Arg::Text                                                                                                                        }}},

        { "[VERSN1]",               { Others::Versn,   {                                                                                                                                  }}},
        { "[VERSN2]",               { Others::Versn,   {                                                                                                                                  }}}
    };
}

namespace Others {
    // ---- Others ---- //
    //QColor CommentFormat = 0x8B8B8B;
    const QColor CommentFormat{ 0x57A64A };
}