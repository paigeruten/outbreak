C_FILES = Dir["*.c"]
H_FILES = Dir["*.h"]
O_FILES = C_FILES.map { |s| s[/[^.]+/] + ".o" }

def find_dependencies(file, h_files = [])
  File.readlines(file).each do |line|
    if line =~ /^#include "([^\/]+\.h)"/ && !h_files.include?($1)
      h_files << $1
      h_files = find_dependencies($1, h_files)
    end
  end

  h_files
end

File.open("Makefile", "w") do |f|
  f << "outbreak: #{O_FILES.join(' ')} SDLMain.m\n"
  f << "\tgcc -o outbreak #{O_FILES.join(' ')} SDLMain.m -framework Cocoa -framework SDL -arch i386\n\n"

  O_FILES.each.with_index do |o_file, i|
    c_file = C_FILES[i]

    f << "#{o_file}: #{c_file} #{find_dependencies(c_file).join(' ')}\n"
    f << "\tgcc -c #{c_file} -arch i386\n\n"
  end

  f << "clean:\n"
  f << "\trm -f *.o outbreak\n"
end

