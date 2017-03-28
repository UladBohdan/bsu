# Task 1.
IP1 = "32.123.211.78"
# Task 2.
IP_list = [
    "255.255.1.0",
    "128.61.0.1",
    "192.201.255.254",
    "214.47.8.160",
    "223.256.72.120",
    "255.255.64.0",
    "218.212.34.255",
    "255.253.254.0",
    "111.111.111.111",
    "203.181.133.64",
    "255.0.0.0",
]
# Task 3.
IP3 = "171.81.144.120"
mask3 = "255.255.255.0"
# Task 4.
IP4 = "196.105.157.223/23"
mask4 = "185.206.219.63/29"

# The algorithm is proposed in the conditions of the problem.
def IP_to_binary(IP):
    # split the string into the array[4]
    splitted = IP.split('.')
    binary = ""
    for ip in splitted:
        num = int(ip)
        if not 0 <= num <= 255:
            return "NOT AN ADDRESS"
        i = 128
        while True:
            if num >= i:
                binary += "1"
                num -= i
            else:
                binary += "0"
            i /= 2
            if i == 0:
                binary += "."
                break
    return binary[:-1]

def IP_or_mask(IP):
    binIP = IP_to_binary(IP)
    if binIP == "NOT AN ADDRESS":
        return "NOT AN ADDRESS"

    # checking if a mask.
    valid_mask = (is_mask(IP) != 0)

    # checking if an IP.
    valid_ip = True
    if int(IP.split('.')[0]) in [0, 10, 127, 255]:
        valid_ip = False

    response = ""
    if valid_ip:
        response += "VALID IP. "
    else:
        response += "INVALID IP. "
    if valid_mask:
        response += "VALID MASK."
    else:
        response += "INVALID MASK."
    return response

def is_mask(mask):
    binMask = IP_to_binary(mask)

    N = 0
    pos = 0

    zero_found = False
    valid_mask = True
    while pos < len(binMask) and valid_mask:
        #print(pos)
        #print(binIP[pos])
        if binIP[pos] == '.':
            pos += 1
            continue
        if (not zero_found) and binIP[pos] == '1':
            pos += 1
            continue
        if zero_found and binIP[pos] == '0':
            pos += 1
            continue
        if (not zero_found) and binIP[pos] == '0':
            zero_found = True
            pos += 1
            continue
        if zero_found and binIP[pos] == '1':
            valid_mask = False
    return valid_mask

def net_address(IP, mask):
    IP_octets = IP.split('.')
    mask_octets = mask.split('.')
    response = ""
    for i in range(0, 4):
        response += str( int(IP_octets[i]) & int(mask_octets[i]) )
        response += "."
    return response[:-1]

f = open("output.txt", 'w')

# Task 1
f.writelines([
    "Task 1\n",
    IP1 + "\n",
    IP_to_binary(IP1) + "\n",
    "\n",
])

# Task 2
f.write("Task 2\n")
for ip in IP_list:
    f.write(ip + "\t\t" + IP_to_binary(ip) + "\t\t" + IP_or_mask(ip) + "\n")
f.write("\n")

# Task 3
f.writelines([
    "Task 3\n",
    "IP:\t\t\t\t"     + IP3   + "\t" + IP_to_binary(IP3)      + "\n",
    "mask:\t\t\t"   + mask3 + "\t" + IP_to_binary(mask3)    + "\n",
    "net address:\t" + net_address(IP3, mask3) + "\t" + IP_to_binary(net_address(IP3, mask3)) + "\n",
])
