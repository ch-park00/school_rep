function r = rect( t, a )
% RECT - rectangular function
%  rect( t, a ) returns 1 for -a/2 < t <= a/2, otherwise returns 0
%   t : Nx1 double, time
%   a : 1x1 double, rectangular pulse width
% 
r = zeros(size(t));
r(abs(t)<=a/2) = 1;
