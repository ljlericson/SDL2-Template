return function(context)
    if context.event == "charScored" then
        local addMult = 0

        if context.char == "K" then
            addMult = addMult + 1
        end

        return {
            addScore = 0,
            mulmultScore = 1,
            addmultScore = addMult
        }
    else
        return {
            addScore = 0,
            mulmultScore = 1,
            addmultScore = 0
        }
    end
end