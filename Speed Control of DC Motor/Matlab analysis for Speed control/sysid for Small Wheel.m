clear;
close all;
clc;
s = tf('s');
pos = readmatrix('smallwheel.txt');

N = 4.4;
counts_per_rev = 48;

T_s = 0.1;

rads = (2*pi*pos)/(N*counts_per_rev);

% omega = zeros(length(rads),1);

for i = 1:length(rads)-1
    omega(i) = (rads(i+1)-rads(i))/T_s; 
end

%t = 0:length(omega);
t= zeros(1, length(rads));




for i = 2:length(t)
    t(i) = t(i-1) + T_s;
end

t = t(1:100);


omega = omega(1:100);
ss = omega(100);
plot(t, omega);


v_app = 12;
k_hat = ss/v_app;

r =0.9*(omega(100));
p = 0.1*(omega(100));

for i = 1:numel(omega)
    if omega(i) > p
        ti = t(i);
        break
    end
end

for i = 1:numel(omega)
    if omega(i) > r
        tq = t(i);
        break
    end
end

tr = tq - ti;
sig = 2.2/tr;

y = v_app*k_hat*(1-exp(-sig*t));

figure(1)
plot(t, y)
hold on
plot(t, omega)
hold off

G_w_small = k_hat*(sig/(s + sig));

figure(2)
step(G_w_small)