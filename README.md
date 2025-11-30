# NetSec Toolkit

A collection of network security and penetration testing tools built from scratch in C.

## 🎯 About

**NetSec Toolkit** is a suite of low-level networking tools designed for security professionals, penetration testers, and anyone interested in understanding how network security tools work under the hood.

All tools are written in C from the ground up, without relying on high-level libraries, to provide deep insight into network protocols, packet manipulation, and security concepts.

## 🛠️ Philosophy

- **Learn by building**: Each tool is crafted from scratch to understand the fundamentals
- **No black boxes**: Direct implementation of networking concepts without abstraction layers
- **Ethical hacking**: All tools are designed for authorized security testing and educational purposes
- **Performance-focused**: Utilizing C's low-level capabilities for efficient network operations

## 📦 Available Tools

### 1. Port Scanner
**Status**: ✅ Complete  
**Location**: `/scanner`

A high-performance multithreaded TCP port scanner with banner grabbing and service detection capabilities.

**Features:**
- Fast concurrent scanning (up to 100 threads)
- Banner grabbing from open ports
- Automatic service identification (HTTP, SSH, FTP, SMTP, SMB)
- Multiple scan modes (open, closed, filtered, all)
- Clean, professional output

[View Documentation →](scanner/README.md)

---

## 🚀 Coming Soon

Additional network security tools are currently in development. Each tool focuses on a specific aspect of network security and penetration testing.

## 🔧 Requirements

- Linux operating system (Debian/Ubuntu recommended)
- GCC compiler
- pthread library
- Root/sudo privileges (for some tools)

## 📚 Learning Resources

Each tool includes:
- Detailed README with usage examples
- Commented source code
- Architecture documentation
- Ethical use guidelines

## 🛡️ Ethical Use & Legal Disclaimer

**IMPORTANT**: These tools are designed strictly for:
- ✅ Educational purposes
- ✅ Authorized security testing
- ✅ Penetration testing with written permission
- ✅ Research in controlled environments

**DO NOT use these tools to:**
- ❌ Attack systems without authorization
- ❌ Scan networks you don't own or have permission to test
- ❌ Perform any illegal activities

Unauthorized use of these tools may violate computer fraud and abuse laws in your jurisdiction. The author assumes no liability for misuse.

## 👤 Author

**Delaskar Caicedo**
- Ethical hacker and security researcher
- Focused on offensive security and low-level network programming

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🤝 Contributing

Contributions, suggestions, and improvements are welcome! Feel free to:
- Open issues for bugs or feature requests
- Submit pull requests with enhancements
- Share feedback on the tools

---

# **⚠️ Use responsibly. Test only on systems you own or have explicit permission to test.**
