-- just a simple script to create the help content for `commands`
local commands = {
	"quit", "open", "show", "save", "back", "help", "history", "bookmarks",
	"set", "see",
}
table.sort(commands)
for i, name in ipairs(commands) do
	io.write(string.format('%-13s ', name))
	if i % 5 == 0 then print() end
end
