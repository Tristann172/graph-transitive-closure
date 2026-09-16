# Warshall Algorithm - Transitive Closure Visualizer

Chương trình trực quan hóa thuật toán **Warshall** để tìm **Ma trận bao đóng truyền nghĩa (Transitive Closure)** của đồ thị có hướng, kết hợp giao diện đồ họa tương tác viết bằng **C++** và thư viện **SFML 3.x**.

---

## Tính năng chính

* **Xử lý thuật toán Warshall:** Chuyển ma trận kề ban đầu thành ma trận bao đóng hoàn chỉnh.
* **Truy vết đường đi (Path Tracing):** Hỗ trợ tìm và in chuỗi các đỉnh kết nối giữa hai nút bất kỳ, tích hợp cơ chế chống vòng lặp vô hạn khi gặp chu trình.
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
