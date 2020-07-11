struct Helper{
	int a;
	long b;
	long long c;
};

void trans(void *helper){
	(Helper*)helper;
	helper->a=10;
	helper->b=20;
	helper->c=30;
}

int main(){


}