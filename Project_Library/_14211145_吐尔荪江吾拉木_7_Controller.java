package homework7;

public class _14211145_吐尔荪江吾拉木_7_Controller {
	private _14211145_吐尔荪江吾拉木_7_BookCatalog bookcatalog = new _14211145_吐尔荪江吾拉木_7_BookCatalog();
	private _14211145_吐尔荪江吾拉木_7_StrategyCatalog strategycatalog = new _14211145_吐尔荪江吾拉木_7_StrategyCatalog();
	private _14211145_吐尔荪江吾拉木_7_Sale sale = new _14211145_吐尔荪江吾拉木_7_Sale();
	public void addBook(String isbn,String title,int type,double price){
		_14211145_吐尔荪江吾拉木_7_BookSpecification booksp = new _14211145_吐尔荪江吾拉木_7_BookSpecification(isbn,title,type,price);
		bookcatalog.addbooks(booksp);
	}
	public void addCompositeStrategy(int type,String str){
		_14211145_吐尔荪江吾拉木_7_CopositeStrategy temp = new _14211145_吐尔荪江吾拉木_7_CopositeStrategy();
		temp.setInfor(str);
		String []str2=str.split("[|]");
		for(int i=0;i<str2.length;i++){
			for(int j=0;j<strategycatalog.getStrategySpecification().size();i++){
				if(str2[i].equals(strategycatalog.getStrategySpecification().get(i).getIsbn())){
					int btype=strategycatalog.getStrategySpecification().get(i).getBooktype();
					temp.add(strategycatalog.getStrategies().get(btype));
				}
			}
		}
		strategycatalog.addstrategy(type, temp);
		
		
	}
	public void addSimpleStrategy(String num,int type,double subP,String name,String strategytype){
		_14211145_吐尔荪江吾拉木_7_IPricingstrategy strategy=null;
		if(type==1||type==3){
			int subp = (int)subP;
			strategy = new _14211145_吐尔荪江吾拉木_7_PercentageStrategy(subp);
		}
		if(type==2){
			strategy = new _14211145_吐尔荪江吾拉木_7_FlatRateStrategy(subP);	
		}
		strategycatalog.addstrategy(type, strategy);
		strategycatalog.addstrategyinfor(type, name, num, strategytype);
	}
	public void deleteStrategy(int type){
		strategycatalog.deletestrategy(type);
		
	}
	public void updateStrategy(String num,double subP){
		_14211145_吐尔荪江吾拉木_7_IPricingstrategy strategy=null;
		int type=0;
		for(int i=0;i<strategycatalog.getStrategySpecification().size();i++){
			System.out.println(strategycatalog.getStrategySpecification().get(i).getIsbn());
			if(num.equals(strategycatalog.getStrategySpecification().get(i).getIsbn())){
				type=strategycatalog.getStrategySpecification().get(i).getBooktype();
				System.out.println(type);
			}
		}
		if(type==1||type==3){
			int subp = (int)subP;
			strategy = new _14211145_吐尔荪江吾拉木_7_PercentageStrategy(subp);
		}
		if(type==2){
			strategy = new _14211145_吐尔荪江吾拉木_7_FlatRateStrategy(subP);	
		}
		strategycatalog.updatastrategy(type, strategy);	
	}
	public void buyBook(int copies,_14211145_吐尔荪江吾拉木_7_BookSpecification book,_14211145_吐尔荪江吾拉木_7_IPricingstrategy strategy){
		
		sale.fun(new _14211145_吐尔荪江吾拉木_7_SaleLineitem(copies,book,strategy));
		for(int i=0;i<sale.getItems().size();i++){
			System.out.println(sale.getItems().get(i).getCopies()+sale.getItems().get(i).getProdSpec().getIsbn());
		}
		
	}
	public _14211145_吐尔荪江吾拉木_7_Sale getSale(){
		return sale;
		
	}
	public _14211145_吐尔荪江吾拉木_7_BookCatalog getbookcatalog(){
		return bookcatalog;
	}
	public _14211145_吐尔荪江吾拉木_7_StrategyCatalog getstrategycatalog(){
		return strategycatalog;
	}

}
