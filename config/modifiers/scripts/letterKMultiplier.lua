return function(context)
    if context.event == "charScored" then
        local points = 0

        if context.char == "K" then
            points = 100
        end

        return {
            addScore = points,
            mulmultScore = 1,
            addmultScore = 0
        }
    else
        return {
            addScore = 0,
            mulmultScore = 1,
            addmultScore = 0
        }
    end
end