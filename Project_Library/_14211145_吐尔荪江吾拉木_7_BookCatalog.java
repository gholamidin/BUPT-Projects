package homework7;

import java.util.ArrayList;

public class _14211145_�¶�ݥ������ľ_7_BookCatalog {
	private ArrayList<_14211145_�¶�ݥ������ľ_7_BookSpecification> books = new ArrayList<_14211145_�¶�ݥ������ľ_7_BookSpecification>();
	public _14211145_�¶�ݥ������ľ_7_BookCatalog(){
		init();
	}
	public _14211145_�¶�ݥ������ľ_7_BookSpecification getBookSpecification(String temp){
		for(int i=0;i<books.size();i++)
		{
			if(books.get(i).getIsbn().equals(temp))
				return books.get(i);
		}
		return null;
	}
	public void addbooks(_14211145_�¶�ݥ������ľ_7_BookSpecification temp){
		books.add(temp);	
	}
	public ArrayList<_14211145_�¶�ݥ������ľ_7_BookSpecification> getBooks() {
		return books;
	}
	public void setBooks(ArrayList<_14211145_�¶�ݥ������ľ_7_BookSpecification> books) {
		this.books = books;
	}
	public void init(){
		books.add(new _14211145_�¶�ݥ������ľ_7_BookSpecification("978-7-302-2","��UML��ģʽӦ��",2,18));
		books.add(new _14211145_�¶�ݥ������ľ_7_BookSpecification("978-7-312-3","��Java��ģʽ��",1,34));
		books.add(new _14211145_�¶�ݥ������ľ_7_BookSpecification("968-6-302-1","��HeadFirst ���ģʽ��",1,58));
		books.add(new _14211145_�¶�ݥ������ľ_7_BookSpecification("958-1-302-2","������˿���ռǡ�",3,30));
		books.add(new _14211145_�¶�ݥ������ľ_7_BookSpecification("900-7-392-2","��������ȫ��",4,20));
	}
	public  _14211145_�¶�ݥ������ľ_7_BookSpecification getbook(String isbn){
		for(int i=0;i<books.size();i++){
			if((books.get(i).getIsbn()).equals(isbn)){
				return books.get(i);
			}
				
		}
		return null;
	}
	 
}
