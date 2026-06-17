#pragma once

#include "Aliases.hpp"

#include <QMap>
#include <QString>

struct CommandRule {
    QColor cmdColor;
    QColorList argColors;

    QColorList colors() const {
        QColorList colors;
        colors.reserve(argColors.size() + 1);

        colors.append(cmdColor);
        colors.append(argColors);

        return colors;
    }
};

namespace Shared {
    // Shared colors //

    const QColor String{ 0xD69D85 };
    const QColor CommentFormat{ 0x57A64A };
}

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
        const QColor Array{ 0x16DF00 };
    }

    namespace Arg {
        // Arguments

        const QColor Class{ 0xFFD700 };
        const QColor Node{ 0xFFFF66 };
        const QColor Field{ 0xFF2836 };
        const QColor SubField{ 0xDF3079 };
        const QColor Property{ 0xB59F38 };
        const QColor Value{ 0xBEB7FF };
        const QColor UIOption{ 0x00CC00 };
        const QColor Option{ 0xFF50FF };
        const QColor InitialFolderFile{ Arg::Class };
        const QColor DestinationFolderFile{ Arg::Node };
        const QColor Parent{ Class };
        const QColor ParentNode{ Node };
        const QColor NodeName{ Shared::String };
        const QColor VaultName{ Node };
        const QColor SourceNode{ Node };
        const QColor TargetNode{ Node };
        const QColor Name{ Shared::String };
    }

    inline const QMap<QString, CommandRule> rules {
        { "add_field",         { Cmd::Field,      { Arg::Class,    Arg::Node,       Arg::Field                     }}},
        { "add_node",          { Cmd::Node,       { Arg::Class,    Arg::ParentNode, Arg::NodeName                  }}},
        { "add_overwrite",     { Cmd::Overwrite,  { Arg::Class,    Arg::ParentNode, Arg::NodeName                  }}},
        { "append_array",      { Cmd::Array,      { Arg::Class,    Arg::Node,       Arg::Field,      Arg::Value    }}},
        { "change_vault",      { Cmd::ChngVlt,    { Arg::Class,    Arg::Node,       Arg::VaultName                 }}},
        { "copy_fields",       { Cmd::Field,      { Arg::Class,    Arg::SourceNode, Arg::TargetNode, Arg::Option   }}},
        { "copy_node",         { Cmd::Node,       { Arg::Class,    Arg::SourceNode, Arg::ParentNode, Arg::NodeName }}},
        { "copy_overwrite",    { Cmd::Overwrite,  { Arg::Class,    Arg::SourceNode, Arg::ParentNode, Arg::NodeName }}},
        { "delete_field",      { Cmd::Field,      { Arg::Class,    Arg::Node,       Arg::Field                     }}},
        { "delete_node",       { Cmd::Node,       { Arg::Class,    Arg::Node                                       }}},
        { "move_node",         { Cmd::Node,       { Arg::Class,    Arg::Node,       Arg::Parent                    }}},
        { "rename_node",       { Cmd::Node,       { Arg::Class,    Arg::Node,       Arg::Name                      }}},
        { "resize_field",      { Cmd::Field,      { Arg::Class,    Arg::Node,       Arg::Field,      Arg::Value    }}},
        { "update_collection", { Cmd::Collection, { Arg::Class,    Arg::Node,       Arg::Field                     }}},
        { "update_field",      { Cmd::Field,      { Arg::Class,    Arg::Node,       Arg::Field                     }}}, /* SPECIALIZED */
        { "ui_text",           { Cmd::UI,         { Shared::String                                                 }}},
        { "ui_control",        { Cmd::UI,         {                                                                }}},
        { "ui_option",         { Cmd::UI,         { Arg::UIOption                                                  }}}
    };
}

namespace Bin {
    // ---- Binary Instructions Set Formats ---- //

    namespace Cmd {
        // Commands
        const QColor InputControl{};
        const QColor Collection{ 0x66ADD8 };
        const QColor InCareer{ 0xEA66BA };
        const QColor String{ 0xBC93F9 };
        const QColor Texture{ 0x00E5FF };
        const QColor Statement{ 0x66FFFF }; // append, delete, else, end, if, import, new, static
        const QColor File{ 0x569CD6 };
        const QColor Folder{ File };
        const QColor Stream{ 0x5D7711 };
        const QColor UIOption{ 0x2596BE };
        const QColor Memory{ 0x44AA11 };
        const QColor SpeedReflect{ 0x8B33FF };
    }

    namespace Arg {
        // Arguments

        const QColor File{ 0x79C8DA };
        const QColor Folder{ 0xFFF59D };
        const QColor Manager{ 0x41B962 };
        const QColor Collection{ 0x81FFF4 };
        const QColor TPKBlock{ 0xC8639F };
        const QColor Type{ 0xFFB300 };
        const QColor FilePath{ 0xFFFF66 };

        const QColor FileName{ File };
        const QColor GCareer{ 0x8AB4F8 };
        const QColor Root{ 0xCC6600 };
        const QColor STRBlock{ TPKBlock };
        const QColor TexPath{ Shared::String };

        const QColor From{ Shared::String };
        const QColor To{ Shared::String };

        const QColor RelativeAbsolute{ Type };

        const QColor KeyLabel{ 0x848884 };
        const QColor DDSPath{ FilePath };

        const QColor Property{ 0xE7EF87 };
        const QColor Value{ 0xFF5555 };

        const QColor Text{ Shared::String };

        const QColor Endscript{ FilePath };

        const QColor Description{ Text };

        const QColor Condition{ 0x991166 };

        const QColor Boolean{ 0x6C99BB };

        const QColor LXRY{ FilePath };
        const QColor STREAMLXRY{ FilePath };
        const QColor UnpackPath{ FilePath };

        const QColor DataPath{ FilePath };

        const QColor Label{ 0xFF3232 };

        const QColor FolderPath{ FilePath };

        const QColor Option{ 0xB2BEB5 };

        const QColor Directory{ File };
    }

    namespace Other {
        const QColor Versn{ 0xFF44FF };
    }

    inline const QMap<QString, CommandRule> rules {
        { "add_collection",         { Cmd::Collection,   { Arg::FileName,         Arg::Manager,          Arg::Collection                                                                    }}},
        { "add_incareer",           { Cmd::InCareer,     { Arg::FileName,         Arg::Manager,          Arg::GCareer,          Arg::Root,       Arg::Collection                            }}},
        { "add_or_replace_texture", { Cmd::Texture,      { Arg::FileName,         Arg::Manager,          Arg::TPKBlock,         Arg::Collection, Arg::Collection, Arg::FilePath             }}},
        { "add_or_update_string",   { Cmd::String,       { Arg::FileName,         Arg::Manager,          Arg::STRBlock,         Arg::KeyLabel,   Arg::Label,      Arg::Text                 }}},
        { "add_string",             { Cmd::String,       { Arg::FileName,         Arg::Manager,          Arg::STRBlock,         Arg::KeyLabel,   Arg::Label,      Arg::Text                 }}},
        { "add_texture",            { Cmd::Texture,      { Arg::FileName,         Arg::Manager,          Arg::TPKBlock,         Arg::Collection, Arg::TexPath                               }}},
        { "append",                 { Cmd::Statement,    { Arg::Endscript                                                                                                                   }}},
        { "bind_textures",          { Cmd::Texture,      { Arg::Type,             Arg::File,             Arg::Manager,          Arg::TPKBlock,   Arg::Folder                                }}}, /* SPECIALIZED */
        { "checkbox",               { Cmd::UIOption,     { Arg::Description                                                                                                                 }}},
        { "combobox",               { Cmd::UIOption,     {                                                                                                                                  }}}, /* SPECIALIZED */
        { "copy_collection",        { Cmd::Collection,   { Arg::FileName,         Arg::Manager,          Arg::From,             Arg::To                                                     }}},
        { "copy_incareer",          { Cmd::InCareer,     { Arg::FileName,         Arg::Manager,          Arg::GCareer,          Arg::Root,       Arg::From,       Arg::To                   }}},
        { "copy_texture",           { Cmd::Texture,      { Arg::File,             Arg::Manager,          Arg::TPKBlock,         Arg::From,       Arg::To                                    }}},
        { "create_file",            { Cmd::File,         { Arg::Type,             Arg::RelativeAbsolute, Arg::Folder                                                                        }}},
        { "create_folder",          { Cmd::Folder,       { Arg::RelativeAbsolute, Arg::FolderPath                                                                                           }}},
        { "delete",                 { Cmd::Statement,    { Arg::FileName                                                                                                                    }}},
        { "erase_file",             { Cmd::File,         { Arg::RelativeAbsolute, Arg::FilePath                                                                                             }}},
        { "erase_folder",           { Cmd::Folder,       { Arg::RelativeAbsolute, Arg::Folder                                                                                               }}},
        { "import",                 { Cmd::Statement,    { Arg::Type,             Arg::File,             Arg::Manager,          Shared::String                                              }}},
        { "if",                     { Cmd::Statement,    { Arg::Condition                                                                                                                   }}}, /* SPECIALIZED */
        { "move_file",              { Cmd::File,         { Arg::Type,             Arg::RelativeAbsolute, Arg::RelativeAbsolute, Arg::From,       Arg::To                                    }}},
        { "new",                    { Cmd::Statement,    { Arg::Type,             Arg::File                                                                                                 }}},
        { "pack_stream",            { Cmd::Stream,       { Arg::LXRY,             Arg::STREAMLXRY,       Arg::DataPath                                                                      }}},
        { "remove_collection",      { Cmd::Collection,   { Arg::File,             Arg::Manager                                                                                              }}},
        { "remove_incareer",        { Cmd::InCareer,     { Arg::File,             Arg::Manager,          Arg::GCareer,          Arg::Root,       Arg::Collection                            }}},
        { "remove_string",          { Cmd::String,       { Arg::File,             Arg::Manager,          Arg::STRBlock,         Arg::KeyLabel                                               }}},
        { "remove_texture",         { Cmd::Texture,      { Arg::File,             Arg::Manager,          Arg::TPKBlock,         Arg::Collection                                             }}},
        { "replace_texture",        { Cmd::Texture,      { Arg::File,             Arg::Manager,          Arg::TPKBlock,         Arg::Collection, Arg::DDSPath                               }}},
        { "speedreflect",           { Cmd::SpeedReflect, { Arg::Directory,                                                                                                                  }}},
        { "static",                 { Cmd::Statement,    { Arg::File,             Arg::Manager,          Arg::Property,         Arg::Value                                                  }}},
        { "stop_errors",            { Cmd::Statement,    { Arg::Boolean                                                                                                                     }}},
        { "unpack_stream",          { Cmd::Stream,       { Arg::LXRY,             Arg::STREAMLXRY,       Arg::UnpackPath                                                                    }}},
        { "unlock_memory",          { Cmd::Memory,       { Arg::FileName                                                                                                                    }}},
        { "update_collection",      { Cmd::Collection,   { Arg::File,             Arg::Manager,          Arg::Collection,       Arg::Property,   Arg::Value                                 }}},
        { "update_incareer",        { Cmd::InCareer,     { Arg::File,             Arg::Manager,          Arg::GCareer,          Arg::Root,       Arg::Collection, Arg::Property, Arg::Value }}},
        { "update_string",          { Cmd::String,       { Arg::File,             Arg::Manager,          Arg::STRBlock,         Arg::KeyLabel,   Arg::Property,   Arg::Value                }}},
        { "update_texture",         { Cmd::Texture,      { Arg::File,             Arg::Manager,          Arg::TPKBlock,         Arg::Collection, Arg::Property,   Arg::Value                }}},
        { "version",                { Cmd::Statement,    { Arg::Value                                                                                                                       }}},
        { "watermark",              { Cmd::Statement,    { Arg::Text                                                                                                                        }}},

        { "[VERSN1]",               { Other::Versn,      {                                                                                                                                  }}},
        { "[VERSN2]",               { Other::Versn,      {                                                                                                                                  }}},

        { "enabled",                { Cmd::Statement,    {                                                                                                                                  }}},
        { "disabled",               { Cmd::Statement,    {                                                                                                                                  }}},
        { "do",                     { Cmd::Statement,    {                                                                                                                                  }}},
        { "else",                   { Cmd::Statement,    {                                                                                                                                  }}},
        { "end",                    { Cmd::Statement,    {                                                                                                                                  }}}
    };
}