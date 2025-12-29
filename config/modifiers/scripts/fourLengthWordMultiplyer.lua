WordList = {}
return function(context)
    if context.event == "wordScored" then

        local wordList = {}
        for index, word in ipairs(context.words) do
            if #word == 3 then
                wordList[index] = word
            end
        end

        local points = 50 * (#wordList - #WordList)
        WordList = wordList

        return {
            addScore = 0,
            mulMultScore = 1,
            addMultScore = 0
        }
    else
        return {
            addScore = 0,
            mulMultScore = 1,
            addMultScore = 0
        }
    end
end