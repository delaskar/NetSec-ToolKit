# NetSec Toolkit - Port Scanner

A high-performance, multithreaded TCP port scanner with banner grabbing and service detection capabilities, built from scratch in C.

## 🎯 Features

- **Fast Multithreaded Scanning**: Leverage up to 100 concurrent threads for rapid port discovery
- **Banner Grabbing**: Automatic service identification and version detection
- **Service Detection**: Recognizes common services (HTTP, SSH, FTP, SMTP, SMB)
- **Flexible Scan Modes**: Scan for open, closed, filtered ports, or all states
- **Professional Output**: Clean, organized results with optional file export
- **Modular Architecture**: Well-structured codebase for easy extension

## 📋 Requirements

- Linux operating system (tested on Debian/Ubuntu)
- GCC compiler
- pthread library
- Basic networking tools

## 🔧 Installation

```bash
# Clone the repository
git clone https://github.com/yourusername/netsec-toolkit.git
cd netsec-toolkit/modulo1_scanner

# Compile the scanner
make

# Clean and rebuild (if needed)
make rebuild
```

## 🚀 Usage

### Basic Syntax

```bash
./scanner [-t <threads>] [-b] <MODE> <Target_IP> <Start_Port> <End_Port>
```

### Flags

- `-t <threads>`: Number of concurrent threads (1-100, default: 1)
- `-b`: Enable banner grabbing and service detection

### Scan Modes

- `open`: Show only open ports
- `closed`: Show only closed ports
- `filtered`: Show only filtered ports
- `all`: Show all port states

### Examples

**Basic sequential scan for open ports:**
```bash
./scanner open 192.168.1.1 1 1000
```

**Fast multithreaded scan:**
```bash
./scanner -t 50 open 192.168.1.1 1 65535
```

**Scan with banner grabbing:**
```bash
./scanner -b open 192.168.1.1 80 443
```

**Full scan with threads and banner detection:**
```bash
./scanner -t 50 -b open 192.168.1.1 1 10000
```

**Scan all port states:**
```bash
./scanner all 127.0.0.1 1 1024
```

## 📊 Sample Output

```
========================================
NetSec Toolkit - Port Scanner
========================================
Target: 192.168.1.100
Port range: 1-1000
Mode: open
========================================

Scan mode: Multithreaded (50 threads)
Banner grabbing: ENABLED

Port 22 - OPEN
  └─ Service: SSH
  └─ Version: SSH-2.0-OpenSSH_8.9p1 Ubuntu-3ubuntu0.1

Port 80 - OPEN
  └─ Service: HTTP
  └─ Version: Apache/2.4.52 (Ubuntu)

Port 443 - OPEN
  └─ Service: HTTP
  └─ Version: nginx/1.18.0

========================================
SCAN SUMMARY
========================================
Target: 192.168.1.100
Ports scanned: 1000
Open ports: 3
Closed ports: 995
Filtered ports: 2
Scan duration: 2.45 seconds
========================================

Results saved to: scan_results.txt
```

## 🏗️ Architecture

```
scanner/
├── include/
│   ├── scanner.h          # Core scanning structures and functions
│   ├── validation.h       # Input validation
│   ├── output.h           # Output formatting
│   ├── utils.h            # Utility functions
│   ├── thread_scanner.h   # Multithreading support
│   └── banner.h           # Banner grabbing and service detection
├── src/
│   ├── main.c             # Entry point and argument parsing
│   ├── scanner.c          # Sequential scanning logic
│   ├── validation.c       # Input validation implementation
│   ├── output.c           # Output formatting and file operations
│   ├── utils.c            # Helper functions
│   ├── thread_scanner.c   # Multithreaded scanning implementation
│   └── banner.c           # Banner grabbing and service fingerprinting
├── obj/                   # Object files (generated)
├── Makefile              # Build configuration
└── README.md             # This file
```

## 🔍 Supported Services

The banner grabbing module can identify:

- **HTTP/HTTPS**: Web servers (Apache, Nginx, IIS, etc.)
- **SSH**: Secure Shell servers with version info
- **FTP**: File Transfer Protocol servers
- **SMTP**: Mail servers
- **SMB**: Windows file sharing (ports 139, 445)
- **Unknown**: Generic services with raw banner display

## ⚙️ Technical Details

### Multithreading

- Uses POSIX threads (pthreads) for concurrent scanning
- Mutex-protected shared resources for thread safety
- Efficient port distribution across worker threads

### Banner Grabbing

- **Passive grabbing**: Receives banners from services that speak first (SSH, FTP)
- **Active probing**: Sends HTTP GET request to services that wait for input
- **Timeout**: 3-second timeout per connection to prevent hanging

### Service Detection

Pattern matching against common service signatures:
- HTTP: Detects `HTTP/` in response and extracts `Server:` header
- SSH: Identifies `SSH-` prefix with full version string
- FTP/SMTP: Recognizes `220 ` response code
- SMB: Port-based detection (139, 445)

## 🛡️ Ethical Use

**IMPORTANT**: This tool is designed for:
- ✅ Educational purposes
- ✅ Authorized security testing
- ✅ Scanning your own systems/networks
- ✅ Penetration testing with written permission

**DO NOT** use this tool to:
- ❌ Scan networks without authorization
- ❌ Perform unauthorized reconnaissance
- ❌ Attack systems you don't own

Unauthorized port scanning may be illegal in your jurisdiction.

## 🤝 Contributing

This is a personal learning project, but suggestions and improvements are welcome!

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Submit a pull request

## 📝 License

This project is released under the MIT License. See LICENSE file for details.

## 👤 Author

**Delaskar**
- Ethical Hacker
- Focus: Offensive security and network penetration testing

## 🙏 Acknowledgments

- Built as part of a comprehensive C programming and penetration testing learning journey
- Inspired by industry-standard tools like Nmap and Masscan
- Developed with guidance on modern security practices and C programming patterns

## 📞 Support

For questions, issues, or suggestions:
- Open an issue on GitHub
- Check existing documentation in `/docs` (coming soon)

---

**⚠️ Disclaimer**: The author assumes no liability for misuse of this tool. Use responsibly and ethically.

**Version**: 1.0.0
**Last Updated**: November 2025
