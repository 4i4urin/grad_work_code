meas_ = load("calib.txt");
meas = meas_(1000:end);
plot(meas);

mid = mean(meas);
disp(mid);
scope = max(meas) - min(meas);
disp(scope);

figure;
freq = fft(meas);
p2 = abs(freq / length(meas));
p1 = p2(1:length(meas) / 2 + 1);
%p1 = p2;
p1(1:end - 1) = 2 * p1(2:end);
f = 1000*(0:(length(meas) / 2)) / length(meas);
plot(f, p1);
