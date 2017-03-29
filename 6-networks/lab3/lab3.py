import numpy as np

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
IPmask4 = "196.105.157.223/23"
IPmask5 = "185.206.219.63/29"

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

# Returns 0 if mask is invalid mask. Returns number of "1" if valid.
def is_mask(mask):
    binMask = IP_to_binary(mask)

    pos = 0
    N = 0

    zero_found = False
    valid_mask = True
    while pos < len(binMask) and valid_mask:
        if binMask[pos] == '.':
            pos += 1
            continue
        if (not zero_found) and binMask[pos] == '1':
            pos += 1
            N += 1
            continue
        if zero_found and binMask[pos] == '0':
            pos += 1
            continue
        if (not zero_found) and binMask[pos] == '0':
            zero_found = True
            pos += 1
            continue
        if zero_found and binMask[pos] == '1':
            valid_mask = False

    if valid_mask:
        return N
    else:
        return 0


def net_address(IP, mask):
    IP_octets = IP.split('.')
    mask_octets = mask.split('.')
    response = ""
    for i in range(0, 4):
        response += str( int(IP_octets[i]) & int(mask_octets[i]) )
        response += "."
    return response[:-1]

def host_part(IP, mask):
    IP_octets = map(lambda octet: np.uint8(octet), IP.split('.'))
    mask_octets = map(lambda octet: np.uint8(octet), mask.split('.'))
    mask_octets_inv = map(lambda octet: ~octet, mask_octets)
    response = ""
    for i in range(0, 4):
        response += str( IP_octets[i] & mask_octets_inv[i] )
        response += "."
    return response[:-1]

def numberOfNodes(mask):
    return str(2**(32-is_mask(mask)) - 2)

def separateIPmask(IPmask):
    splitted = IPmask.split("/")
    mask = ""
    for i in range(0, int(splitted[1])):
        if i % 8 == 0 and i != 0:
            mask += "."
        mask += "1"
    for i in range(int(splitted[1]), 32):
        if i % 8 == 0 and i != 0:
            mask += "."
        mask += "0"
    mask_spl = map(lambda octet: int(octet, base=2), mask.split("."))
    mask = ""
    for i in range(0, len(mask_spl)):
        mask += str(mask_spl[i])
        mask += "."
    return (splitted[0], mask[:-1])

def firstIPinNetwork(net_addr, mask):
    octets = map(lambda x: int(x), net_addr.split("."))
    octets[3] += 1
    ip = ""
    for i in range(0, len(octets)):
        ip += str(octets[i])
        ip += "."
    return ip[:-1]

def lastIPinNetwork(net_addr, mask):
    broadcasting_splitted = map(lambda x: int(x), broadcasting_address(net_addr, mask).split("."))
    broadcasting_splitted[-1] -= 1
    last_ip = ""
    for i in range(0, 4):
        last_ip += str(broadcasting_splitted[i])
        last_ip += "."
    return last_ip[:-1]

def broadcasting_address(net_addr, mask):
    net_addr_splitted = map(lambda x: np.uint8(x), net_addr.split("."))
    mask_splitted_inversed = map(lambda x: ~np.uint8(x), mask.split("."))
    broadcasting = ""
    for i in range(0, 4):
        broadcasting += str( net_addr_splitted[i] | mask_splitted_inversed[i] )
        broadcasting += "."
    return broadcasting[:-1]

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
    "host part:\t\t" + host_part(IP3, mask3) + "\t\t" + IP_to_binary(host_part(IP3, mask3)) + "\n",
    "potential number of nodes: " + numberOfNodes(mask3) + "\n",
    "\n",
])

# Task 4
IP4, mask4 = separateIPmask(IPmask4)
net_address4 = net_address(IP4, mask4)
f.writelines([
    "Task4 - example1\n",
    "IP: \t\t\t" + IP4 + "\t" + IP_to_binary(IP4) + "\n",
    "Mask: \t\t\t" + mask4 + "\t" + IP_to_binary(mask4) + "\n",
    "Net address: \t" + net_address4 + "\t" + IP_to_binary(net_address4) + "\n",
    "Number of nodes:\t" + numberOfNodes(mask4) + "\n",
    "First IP in network:\t" + firstIPinNetwork(net_address4, mask4) + "\n",
    "Last IP in network:\t\t" + lastIPinNetwork(net_address4, mask4) + "\n",
    "Broadcasting address:\t" + broadcasting_address(net_address4, mask4) + "\n",
    "\n",
])

IP5, mask5 = separateIPmask(IPmask5)
net_address5 = net_address(IP5, mask5)
f.writelines([
    "Task4 - example2\n",
    "IP: \t\t\t" + IP5 + "\t" + IP_to_binary(IP5) + "\n",
    "Mask: \t\t\t" + mask5 + "\t" + IP_to_binary(mask5) + "\n",
    "Net address: \t" + net_address5 + "\t" + IP_to_binary(net_address5) + "\n",
    "Number of nodes:\t" + numberOfNodes(mask5) + "\n",
    "First IP in network:\t" + firstIPinNetwork(net_address5, mask5) + "\n",
    "Last IP in network:\t\t" + lastIPinNetwork(net_address5, mask5) + "\n",
    "Broadcasting address:\t" + broadcasting_address(net_address5, mask5) + "\n",
    "\n",
])
