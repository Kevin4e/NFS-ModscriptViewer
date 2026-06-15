version = open("../VERSION.txt").read().strip() 

# Qt header (added quotes to 'w', fixed '\n', and used forward slashes)
open("../src/version.hpp", 'w').write(f'#define APP_VERSION "{version}"\n') 

# Inno Setup include file
open("../setup/version.iss.inc", 'w').write(f'#define MyAppVersion "{version}"\n')