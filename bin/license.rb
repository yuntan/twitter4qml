#!/usr/bin/ruby

license = '/* '

File.open('./LICENSE', 'r') do |file|
    license += file.collect do |line|
        line
    end.join(' * ')
end

license += " */\n\n"

ARGV.each do |target|
    File.open(target, 'r+') do |file|
        state = 0
        lines = []
        file.each do |line|
            case state
            when 0  # start
                if line =~ /^\/\*/ # in license header
                    state = 1
                else # no license header
                    state = 2
                    lines.push license
                    lines.push line
                end
            when 1 # in state header
                if line =~ /\*\/$/ # end of license header
                    state = 2
                    lines.push license
                end
            when 2 # contents
                lines.push line
            end
        end

        file.rewind
        file.write lines.join('')
    end
end
