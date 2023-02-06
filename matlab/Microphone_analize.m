clear;
meas_ = load("calib.txt");
%meas_ = load("music.txt");
meas = meas_;%(1000:end);
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
Fs = 40000;
f = Fs*(0:(length(meas) / 2)) / length(meas);
plot(f, p1);
hold on; grid on;

meas_mean = mean(p1);
y_mean = zeros(length(f));
for i = 1:length(f)
    y_mean(i) = meas_mean;
end
disp("сренее по граифку частот");
disp(meas_mean);
plot(f, y_mean);
disp("length(fft)=")
disp(length(p1));
fft = p1;
for i = 1:3
    fft = find_peaks(fft);
    figure;
    plot(f, fft);
    grid on; hold on;
end
%how find picks?

function fft = find_peaks(fft)
    peak = max(fft);
    pos = find(fft == peak);
    for i = pos:length(fft)-2 % to right
        last_num = fft(i);
        num = fft(i + 1);
        next_num = fft(i + 2);
        if (last_num < num) && (num < next_num)
            break;
        end
    end
    %disp("kek");
    for j = pos:-1:3
        last_num = fft(j);
        num = fft(j - 1);
        next_num = fft(j - 2);
        if (last_num < num) && (num < next_num)
            break;
        end
    end
    right_indx = i;
    left_indx = j;
    disp("right indx");
    disp(right_indx);
    disp("position")
    disp(pos);
    disp("left indx");
    disp(left_indx);
    fft = cut_from_arr(fft, right_indx, left_indx, mean(fft));
    %f = cut_from_arr(f, right_indx, left_indx);
end

function arr = cut_from_arr(arr, ri, li, val)
    for i = li:1:ri
        arr(i) = val;
    end
end
















