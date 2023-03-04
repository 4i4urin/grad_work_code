clear;
m_meas = load("spi.txt");
m_res = fft(m_meas);
m_res(1) = 0;
plot(abs(m_res));
grid on; hold on;

c_res = load("res_fft_c.txt");
plot(c_res);
