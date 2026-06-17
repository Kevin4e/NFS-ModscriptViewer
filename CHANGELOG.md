# Changelog

## [v0.2.0] - 2026-06-18

### Added
- Improved syntax tokenization system via `splitCommandLine()` utility
- Extended syntax highlighting coverage:
  - Better string literal detection (Binary)
  - Improved comment highlighting (`#` and `//`)
  - Extended highlighting rules for Binary

---

### Changed
- Major refactor of syntax highlighting architecture:
- Rule-based system centralized in `ColorFormats.hpp`
- Cleaned up the command-to-format mapping
- Improved `Highlighter` logic:
  - More robust token-based parsing
  - Context-aware handling of special commands (`update_field`, `if`, `combobox`, etc.)
- Enhanced Binary language highlighting:
  - Better handling of strings and comments
  - Specialized command formatting for complex instructions
- UI title handling improved to reflect modified state (`*file` indicator)
- Overall code cleanup
- Minor performance improvements

---

### Fixed
- Improved robustness of command parsing and token alignment in syntax highlighting (reduces mis-coloring edge cases)
- Safer process handling for external executable termination across platforms
- General stability improvements from refactoring of highlighter logic

---

## [v0.1.0] - 2026-06-15

### Added
- Initial release of NFS-ModscriptViewer
- Basic text editor based on Qt QTextEdit
- File system support (open, save, save as)
- Command-line file opening support
- Syntax highlighting system for:
  - Attribulator language
  - Binary language
- Rule-based highlighting engine using command/argument mapping
- Context-sensitive highlighting for complex commands (e.g. `update_field`)
- About dialog with version display
- Support dialog with GitHub issue link and Discord contact
- Line spacing adjustment system (increase, decrease, custom value)
- Status bar line counter
- Menu system with shortcuts (Ctrl+O, Ctrl+S, etc.)

---
### Changed
- N/A

---
### Fixed
- N/A