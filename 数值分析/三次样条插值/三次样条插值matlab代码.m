%���ȵ���ڵ�xi,yi����ֵ,��f"��a����f"��b����
X=input('���û�����ڵ�xi��i=0,1...n)����ɵľ���:');
Y=input('���û�����ڵ�yi��i=0,1...n)����ɵľ���:');
M0=input('������f"��a����ֵ��');
Mn=input('������f"��b����ֵ��');
%��hi������H��
n=length(X);
H=zeros(1,n);
for i=2:n
    H(i)=X(i)-X(i-1);
end
%��miu i����miu��,��lanmuda i����lanmuda�У���di ����D��
miu=ones(1,n-1);lanmuda=ones(1,n-1);D=zeros(1,n-1);
for i=2:(n-1)
    miu(i)=H(i)/(H(i)+H(i+1));
    lanmuda(i)=1-miu(i);
    D(i)=6/(H(i)+H(i+1))*((Y(i+1)-Y(i))/H(i+1)-(Y(i)-Y(i-1))/H(i));
end
%������ط��̣�A*M=b��ϵ������A��b,M
%��A��
A=zeros(n-2);
for i=1:(n-2)
    A(i,i)=2;
end
for i=1:(n-3)
    A(i,i+1)=lanmuda(i+1);
end
for i=2:(n-2)
    A(i,i-1)=miu(i+1);
end
%��b��
b=zeros(1,(n-2))';
b(1)=D(2)-miu(2)*M0;
for i=2:(n-3)
    b(i)=D(i+1);
end
b(n-2)=D(n-1)-lanmuda(n-1)*Mn;
M=[M0,(inv(A)*b)',Mn];
%S(x)�γɵľ���S
S=zeros(n-1,4);
for i=1:(n-1)
    syms x;
   p=((X(i+1)-x)^3)/(6*H(i+1))*M(i)+((x-X(i))^3)/(6*H(i+1))*M(i+1)...
       +(Y(i)-(H(i+1)^2)/6*M(i))*(X(i+1)-x)/H(i+1)+...
       (Y(i+1)-(H(i+1)^2)/6*M(i+1))*(x-X(i))/H(i+1);
   S(i,:)=coeffs(p,x);
end
%�������
for i=1:n-1
    fprintf('��x(%d)��x(%d):%f+(%f)*x+(%f)*x^2+(%f)*x^3\n',...
        i-1,i,S(i,1),S(i,2),S(i,3),S(i,4))
end


