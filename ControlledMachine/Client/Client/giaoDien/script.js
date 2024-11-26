// script.js

document.getElementById('sendButton').addEventListener('click', function() {
    const ipAddress = document.getElementById('ipAddress').value;
    const message = document.getElementById('message').value;

    fetch('http://127.0.0.1:55555', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({ message: message, ip: ipAddress })
    })
    .then(response => {
        if (response.ok) {
            console.log('Thông điệp đã được gửi thành công!');
        } else {
            console.error('Gửi thông điệp không thành công.');
        }
    })
    .catch(error => {
        console.error('Lỗi:', error);
    });
});

document.addEventListener('DOMContentLoaded', () => {
    const messageInput = document.getElementById('message');
    const ipInput = document.getElementById('ipAddress'); // Nhập địa chỉ IP
    const sendButton = document.getElementById('sendButton');

    sendButton.addEventListener('click', () => {
        const message = messageInput.value.trim();
        const ipAddress = ipInput.value.trim();

        if (message === '' && ipAddress === '') {
            showNotification('Vui lòng nhập địa chỉ ip và thông điệp trước khi gửi!', 'error');
        }
        else if (message !== '' && ipAddress === '') showNotification('Vui lòng nhập địa chỉ ip trước khi gửi!', 'error');
        else if (message === '' && ipAddress !== '') showNotification('Vui lòng nhập thông điệp trước khi gửi!', 'error');
        else {
            messageInput.value = '';
            showNotification('Thông điệp đã được gửi thành công!');
        }
        
        // if (message !== '' ||) {
        //     // Mô phỏng việc gửi thông điệp (bạn có thể thay bằng logic gửi thực tế)
        //     console.log('Đã gửi thông điệp:', message);

        //     // Xóa nội dung của ô nhập liệu
        //     messageInput.value = '';

        //     // Tạo một thông báo nhỏ trên giao diện
        //     showNotification('Thông điệp đã được gửi thành công!');
        // } else {
        //     showNotification('Vui lòng nhập thông điệp trước khi gửi.', 'error');
        // }
        // if (message !== '' && ipAddress !== '') {
        //     fetch('http://127.0.0.1:55555', {
        //         method: 'POST',
        //         headers: {
        //             'Content-Type': 'application/json'
        //         },
        //         body: JSON.stringify({ message: message, ip: ipAddress })
        //     })
        //     .then(response => {
        //         if (response.ok) {
        //             console.log('Thông điệp đã được gửi thành công!');
        //             showNotification('Thông điệp đã được gửi thành công!');
        //             messageInput.value = ''; // Xóa ô nhập liệu
        //         } else {
        //             console.error('Gửi thông điệp không thành công.');
        //             showNotification('Gửi thông điệp không thành công.', 'error');
        //         }
        //     })
        //     .catch(error => {
        //         console.error('Lỗi:', error);
        //         showNotification('Đã xảy ra lỗi.', 'error');
        //     });
        // } else {
        //     showNotification('Vui lòng nhập thông điệp và địa chỉ IP trước khi gửi.', 'error');
        // }
    });

    function showNotification(message, type = 'success') {
        const notification = document.createElement('div');
        notification.className = `notification ${type}`;
        notification.textContent = message;

        document.body.appendChild(notification);

        setTimeout(() => {
            notification.style.opacity = '0';
        }, 2000);

        setTimeout(() => {
            notification.remove();
        }, 3000);
    }
});
