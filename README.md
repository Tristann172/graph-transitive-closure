# Warshall Algorithm - Transitive Closure Visualizer

Chương trình trực quan hóa thuật toán **Warshall** để tìm **Ma trận bao đóng truyền nghĩa (Transitive Closure)** của đồ thị có hướng, kết hợp giao diện đồ họa tương tác viết bằng **C++** và thư viện **SFML 3.x**.

---

## Tính năng chính

* **Xử lý thuật toán Warshall:** Chuyển ma trận kề ban đầu thành ma trận bao đóng hoàn chỉnh.
* **Truy vết đường đi (Path Tracing):** Hỗ trợ tìm và in chuỗi các đỉnh kết nối giữa hai nút bất kỳ, tích hợp cơ chế chống lặp vô hạn khi gặp chu trình.
* **Đa dạng nguồn nhập liệu:** Hỗ trợ đọc từ file cấu hình `input.txt` nhiều test case hoặc nhập thủ công từ bàn phím.
* **Giao diện đồ họa SFML trực quan (Dark Neon Mode):**
  * Hiển thị bảng ma trận kề gốc và ma trận bao đóng song song.
  * Vẽ đồ thị hình học tương tác với hiệu ứng phát sáng chuyển động (pulse animation).
  * Bảng thống kê số đỉnh, số cạnh trước/sau khi chạy thuật toán và khối chú thích chi tiết.

---

## Cấu trúc thư mục

```text
├── Common.h            # Định nghĩa bảng màu, hằng số và kiểu dữ liệu chung
├── WarshallLogic.h     # Khai báo các hàm thuật toán và xử lý console
├── WarshallLogic.cpp   # Hiện thực Warshall, đọc dữ liệu và truy vết đường đi
├── GraphGUI.h          # Khai báo các hàm vẽ đồ họa giao diện SFML
├── GraphGUI.cpp        # Hiện thực rendering đồ thị, ma trận và hiệu ứng
├── main.cpp            # Điểm khởi chạy chương trình (Entry point)
├── input.txt           # Dữ liệu mẫu các test case
└── .gitignore          # Cấu hình bỏ qua file thực thi và thư viện liên kết
```

---

## Yêu cầu hệ thống

* **Trình biên dịch:** GCC/MinGW-w64 hỗ trợ chuẩn `C++17` trở lên.
* **Thư viện:** SFML 3.x (Graphics, Window, System).
* **Hệ điều hành:** Windows.

---

## Hướng dẫn cài đặt & Biên dịch

### 1. Biên dịch mã nguồn

Mở terminal tại thư mục dự án và chạy lệnh sau (chỉnh lại đường dẫn thư mục SFML trên máy nếu khác):

```bash
g++ -std=c++17 main.cpp WarshallLogic.cpp GraphGUI.cpp -o main.exe -I"C:/SFML-3.0.2/include" -L"C:/SFML-3.0.2/lib" -lsfml-graphics -lsfml-window -lsfml-system
```

### 2. Chuẩn bị thư viện liên kết động (DLL)

Sao chép các file `.dll` từ thư mục `bin` của SFML (`sfml-graphics-3.dll`, `sfml-window-3.dll`, `sfml-system-3.dll`,...) vào cùng thư mục với file `main.exe`.

### 3. Chạy chương trình

```bash
./main.exe
```

---

## Hướng dẫn sử dụng

1. **Chọn chế độ nhập dữ liệu trên Terminal:**
   * Nhấn `1`: Đọc bộ test case từ file `input.txt`.
   * Nhấn `2`: Nhập số lượng đỉnh và ma trận kề trực tiếp từ bàn phím.
2. **Xem hiển thị đồ họa:** Cửa sổ SFML sẽ xuất hiện mô phỏng đồ thị và ma trận kết quả. Nhấn phím **SPACE** trên cửa sổ để quay lại console.
3. **Truy vết đường đi:** Nhập đỉnh bắt đầu và đỉnh kết thúc để theo dõi chuỗi di chuyển (hoặc nhập `0` để thoát).
