Log:Add("Hi from Lua!")

local t = connectedEntity:GetComponent_Transform()
local transformCheck = connectedEntity:HasComponent_Transform()

local v = vec3f(10.0,10.0,10.0)


Log:Add("New Vec3 X Value : " .. tostring(v.x))
Log:Add("This entity has a transform component ? : " .. tostring(transformCheck))

function OnUpdate(deltaTime)
	v.x = v.x+50*deltaTime
	t:SetRotation(v)
end