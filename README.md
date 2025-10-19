# RC4_Project

## Giới thiệu

Đây là dự án minh họa thuật toán **RC4** sử dụng ngôn ngữ **C**, với hai chương trình riêng biệt:

- **RC4_Encrypt_C**: mã hóa chuỗi plaintext thành ciphertext (xuất ra dạng hex)
- **RC4_Decrypt_C**: giải mã chuỗi hex trở lại plaintext

Mục tiêu là để bạn thể hiện được:

- tổ chức mã theo kiểu thư viện (header + source)
- tách mã hóa & giải mã thành 2 project độc lập
- main chỉ gọi hàm từ thư viện
- sử dụng Git / GitHub để quản lý và nộp bài

---

## 📁 Cấu trúc thư mục

```bash
RC4_Project/
├── README.md
├── RC4_Encrypt_C/
│   ├── main.c
│   ├── rc4.c
│   ├── rc4.h
│   └── encrypt.exe ← (sau khi build)
├── RC4_Decrypt_C/
│   ├── main.c
│   ├── rc4.c
│   ├── rc4.h
│   └── decrypt.exe ← (sau khi build)
```

- Thư viện `rc4.c` / `rc4.h` được copy vào cả hai project để mỗi project tự lập.
- `main.c` chỉ làm nhiệm vụ gọi hàm, xuất / nhập dữ liệu.
- File thực thi (`encrypt.exe`, `decrypt.exe`) sẽ được tạo khi bạn build code.

---

## Cách biên dịch & chạy

```bash
# --- Mã hóa ---
cd RC4_Project/RC4_Encrypt_C
gcc main.c rc4.c -o encrypt.exe
./encrypt.exe

# --- Giải mã ---
cd RC4_Project/RC4_Decrypt_C
gcc main.c rc4.c -o decrypt.exe
./decrypt.exe
```

- Chương trình mã hóa sẽ in ra ciphertext (chuỗi hex).
- Bạn sao chép chuỗi hex đó để đưa vào phần giải mã.
- Trong main.c của dự án giải mã, tìm dòng:
  `const char *hex_cipher = "PUT_HEX_OUTPUT_HERE";`
  và thay PUT_HEX_OUTPUT_HERE bằng chuỗi hex bạn thu được từ chương trình mã hóa.
- Kết quả mẫu khi chạy:
  `Decrypted text: Hanoi University of Science and Technology`
