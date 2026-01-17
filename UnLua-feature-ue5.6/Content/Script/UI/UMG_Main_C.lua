---@type UMG_Main_C
local M = UnLua.Class()

function M:Construct()
	self.ExitButton.OnClicked:Add(self, M.OnClicked_ExitButton)	
	--self.ExitButton.OnClicked:Add(self, function(Widget) UE.UKismetSystemLibrary.ExecuteConsoleCommand(Widget, "exit") end )
	self.BtnTest.OnClicked:Add(self, self.qqq)
end

function M:qqq()
	self.TxtTest:SetText(self.TxtTest:GetText() .. 'a')
end

function M:OnClicked_ExitButton()
	UE.UKismetSystemLibrary.ExecuteConsoleCommand(self, "exit")
end

return M
