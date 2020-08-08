function xp = fx1(x_prev,T,gam,g,rho)

xp(1,1) = x_prev(1) + T*x_prev(2);
xp(2,1) = x_prev(2) + T*rho*exp(-x_prev(1)/gam)*x_prev(2)^2*x_prev(3)/2-T*g;
xp(3,1) = x_prev(3);

end