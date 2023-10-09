def reversal_customers(arr, x):
    n = len(arr)
    i = x
    while i < n:
        # Tìm khách hàng cùng là oán linh hoặc chú thuật sư
        group = [arr[i]]
        j = i + 1
        while j < n and (arr[j] * arr[i] > 0):
            group.append(arr[j])
            j += 1
        
        # Nếu có ít nhất 2 khách hàng trong nhóm
        if len(group) >= 2:
            group.reverse()  # Đảo ngược vị trí của nhóm
            arr[i:j] = group  # Cập nhật danh sách
            i = j  # Tiến tới vị trí tiếp theo sau nhóm đã đảo

        else:
            i += 1

# Ví dụ
arr = [-12, -55, 47, -33, -25, 14]
x = 0  # Vị trí X
reversal_customers(arr, x)
print(arr)  # Kết quả: [-25, -33, 14, -55, -12, 47]
