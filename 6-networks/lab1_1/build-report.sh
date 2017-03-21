# A bash script to generate a pdf report for lab1 part1.
# Tested on macOS 10.12.3 Sierra.

# Creating a template for report.
REPORT_TEMPLATES="report_templates"
REPORT_TEX_FILE="report.tex"
REPORT_TEMP_PDF="report.pdf"
REPORT_FINAL_PDF="Lab1_part1_Bohdan.pdf"
cat "$REPORT_TEMPLATES/report_header.tex" > $REPORT_TEX_FILE
echo "\input{$REPORT_TEMPLATES/title.tex}" >> $REPORT_TEX_FILE

function print_title_and_command_output() {
    echo "\subsection*{$1}
    \begin{verbatim}" >> $REPORT_TEX_FILE
    eval "$2" >> $REPORT_TEX_FILE
    echo "\end{verbatim}" >> $REPORT_TEX_FILE
}

# 1. hostname
echo "\section{hostname util}
\begin{verbatim}" >> $REPORT_TEX_FILE
hostname >> $REPORT_TEX_FILE
echo "\end{verbatim}" >> $REPORT_TEX_FILE

# 2. ipconfig
echo "\section{ipconfig}" >> $REPORT_TEX_FILE
print_title_and_command_output "IP-address" "ipconfig getifaddr en0"
print_title_and_command_output "Subnet mask" "ipconfig getoption en0 subnet_mask"
print_title_and_command_output "Gateway" "route get default |  awk '/gateway/{print $2}'"
print_title_and_command_output "DHCP address" "ipconfig getoption en0 server_identifier"
print_title_and_command_output "Mac address" "ifconfig en1 | awk '/ether/{print $2}'"
print_title_and_command_output "DNS server" "ipconfig getoption en0 domain_name_server"

# 3. ping
echo "starting ping..."
echo "\section{ping}" >> $REPORT_TEX_FILE
print_title_and_command_output "10.150.1.5" "ping 10.150.1.5 -c 4"
print_title_and_command_output "10.150.1.1" "ping 10.150.1.1 -c 4"
print_title_and_command_output "10.0.0.20" "ping 10.0.0.20 -c 4"
print_title_and_command_output "10.150.6.29" "ping 10.150.6.29 -c 4"
print_title_and_command_output "10.150.3.30" "ping 10.150.3.30 -c 4"
print_title_and_command_output "google.com.by" "ping google.com.by -c 3 -s 1000"
print_title_and_command_output "velcom.by" "ping velcom.by -c 3 -s 1000"
print_title_and_command_output "localhost" "ping localhost -c 5"

# 4. tracert
echo "starting traceroute..."
echo "\section{traceroute}" >> $REPORT_TEX_FILE
print_title_and_command_output "traceroute google.com.by" "traceroute google.com.by"
print_title_and_command_output "traceroute -m 7 velcom.by" "traceroute -m 7 velcom.by"

# 5. arp
echo "\section{arp}" >> $REPORT_TEX_FILE
print_title_and_command_output "arp -a" "arp -a"

# 6. netstat
echo "\section{netstat}" >> $REPORT_TEX_FILE
print_title_and_command_output "netstat -p TCP" "netstat -p TCP"
print_title_and_command_output "netstat -np TCP" "netstat -np TCP"
print_title_and_command_output "netstat -a -s -r" "netstat -a -s -r"
echo "Flag description:\\\\
-a, --all - Show both listening and non-listening (for TCP this means established connections) sockets.\\\\
-s, --statistics - Display summary statistics for each protocol.\\\\
-r, --route - Display the kernel routing tables.\\\\" >> $REPORT_TEX_FILE

# 7. nslookup
echo "\section{nslookup}" >> $REPORT_TEX_FILE
print_title_and_command_output "nslookup 10.150.5.44" "nslookup 10.150.5.44"

# 8. route table
echo "\section{route table}" >> $REPORT_TEX_FILE
print_title_and_command_output "netstat -rn" "netstat -rn"

# Completing tex sources.
echo "\end{document}" >> $REPORT_TEX_FILE

# Compiling report from tex sources.
pdflatex $REPORT_TEX_FILE
rm $REPORT_TEX_FILE
mv $REPORT_TEMP_PDF $REPORT_FINAL_PDF
open $REPORT_FINAL_PDF
