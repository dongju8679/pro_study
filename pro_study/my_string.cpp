#include <iostream>

int my_strlen(char* str);
int my_strcpy(char* dst, char* src);
int my_strcmp(char* strA, char* strB);

int main(int argc, char *argv[]) {
	int ret = 0;
	char A[100] = "adgasdab";
	char B[100] = "";
	char C[100] = "dsjfiejef";
	char D[52] = "dsjfiejef";
	
	char A1[10] = "chighick";
	char B2[10] = "ablxck";
	char C3[10] = "chighick";

	std::cout << "my_strlen = " << my_strlen(A) << std::endl;
	std::cout << "before B = " << B << std::endl;
	std::cout << "before A = " << A << std::endl;
	std::cout << "my_strcpy(B, A) = " << my_strcpy(B, A) << std::endl;
	std::cout << "after B = " << B << std::endl;
	std::cout << "after A = " << A << std::endl;
	std::cout << "my_strcmp(C, D) = " << my_strcmp(C, D) << std::endl;
	//std::cout << "A = " << A << std::endl;
	//std::cout << "B = " << B << std::endl;
	//printf("A = %s\n", A);
	//printf("B = %s\n", B);

	return ret;
}

#if 0
int my_strlen(char *str) {
	int ret = 0;
	char *ptr = str;
	//std::cout << "ptr + 1 = " << ptr + 1<< std::endl;
#if 1
	while (*ptr != '\0') {
		//printf("before ret = %d, *ptr = %c\n", ret, *ptr);
		ret = ret + 1;
		//printf("after ret = %d, *ptr = %c\n", ret);
		ptr++;
	}
#endif
	return ret;
}

int my_strcpy(char *dst, char *src) {
	int ret = 0;
	//char *ptr = src;

	while (1) {
		//printf("before src = %c, dst = %c\n", *src, *dst);
		if (*src == '\0') {
			break;
		}
		*dst = *src;
		//printf("after src = %c, dst = %c\n", *src, *dst);
		dst++;
		src++;
		ret++;
	}
	*dst = '\0';
	return ret;
}

int my_strcmp(char *strA, char *strB) {
	int ret = 0;
	while (1) {
		if (*strA == '\0' || *strB == '\0') {
			break;
		}
		if (*strA == *strB) {
			ret = 0;
		}
		else if (*strA > *strB) {
			ret = 1;
			break;
		}
		else if (*strA < *strB) {
			ret = -1;
			break;
		}
		strA++;
		strB++;
	}
	return ret;
}

#else
int my_strcpy(char *dst, char *src) {
	int ret = 0;
	int i = 0;
	while (1) {
		if (src[i] == '\0') {
			break; 
		}
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	ret = i;
	return ret;
}

int my_strcmp(char *str1, char *str2) {
	int ret = 0;
	int i = 0;

	while (1) {
		if (str1[i] == '\0' || str2[i] == '\0')  {
			break; 
		}
#if 0
		if (str1[i] > str2[i]) {
			ret = 1;
			break;
		} else if (str1[i] < str2[i]) {
			ret = -1;
			break;
		}
#else
		if (str1[i] != str2[i]) {
			ret = str1[i] - str2[i];
			break;
#endif
		} else if (str1[i] == str2[i]) {
			ret = 0;
		}
		i++;
	}
	return ret;
}

int my_strlen(char *str) {
	int ret = 0;
	int i = 0;
	while (1) {
		if (str[i] == '\0') {
			break;
		}
		i++;
	}
	ret = i;
	return ret;
}
#endif
