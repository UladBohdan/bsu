# The task
func = lambda { |x| x * Math.log(x) - x**2 * Math.cos(x) }
l = 1.0
r = 3.0
n_values = [2, 3, 4, 5]

# Function to count divided difference for array of values
def get_div_diff(x, f)
    case x.length
    when 0 then 1
    when 1 then f.call x[0]
    when 2 then (f.call(x[0]) - f.call(x[1])) / (x[0] - x[1])
    else (get_div_diff(x[0..-2], f) - get_div_diff(x[1..-1], f)) / (x[0] - x[-1])
    end
end

n_values.each do |n|
    print "n = #{n}: "
    x = []
    temp = l
    n.times { x.push(temp); temp += (r - l) / (n - 1) }
    n.times do |i|
        print "(#{get_div_diff(x[0..i], func).round(5)})"
        print "*" unless i == 0
        i.times { |j| print "(x-#{x[j].round(5)})"; print "*" unless j == i-1 }
        print " + " unless i == n-1
    end
    puts
end
