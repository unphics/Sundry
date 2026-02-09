echo build begin
xmake f -c
xmake f -p android -a arm64-v8a -v
xmake install
xmake run
echo build end