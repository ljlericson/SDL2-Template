WordList = {}
return function(context)
    if context.event == "wordPlaced" then

        local wordList = {}
        for index, word in ipairs(context.words) do
            if #word == 4 then
                wordList[index] = word
            end
        end

        local points = 50 * (#wordList - #WordList)
        WordList = wordList

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