print('test.lua')

ctest("lua string", 6, true)

ctestarr({"q", "w", "e"})

local a = {}
a['name'] = 'ikun'
a['age'] = '18'
ctestmap(a, 18)