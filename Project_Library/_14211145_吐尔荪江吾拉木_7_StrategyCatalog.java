package homework7;

import java.util.ArrayList;
import java.util.HashMap;

public class _14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_StrategyCatalog {
	private HashMap<Integer, _14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_IPricingstrategy> strategies=new HashMap<Integer, _14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_IPricingstrategy>();
	private ArrayList<_14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_StrategySpecification> strategy = new ArrayList<_14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_StrategySpecification>();
	public _14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_StrategyCatalog(){
		init();
	}
	public HashMap<Integer, _14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_IPricingstrategy> getStrategies() {
		return strategies;
	}
	public _14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_IPricingstrategy getstrategy(int type){
		if(strategies.get(type).equals(null)){
			return null;
		}
		else
			return strategies.get(type);
			
	}

	public void setStrategies(
			HashMap<Integer, _14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_IPricingstrategy> strategies) {
		this.strategies = strategies;
	}
	public void addstrategy(int type,_14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_IPricingstrategy strategy){
		strategies.put(type, strategy);
	}
	public void addstrategyinfor(int booktype,String name,String isbn,String strategytype){
		strategy.add(new _14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_StrategySpecification(booktype,name,isbn,strategytype));
	}
	public void deletestrategy(int type){
		strategies.remove(type);
		for(int i=0;i<strategy.size();i++){
			if(strategy.get(i).getBooktype()==type){
				strategy.remove(i);
				break;
			}
		}
		
	}
	public void updatastrategy(int type,_14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_IPricingstrategy strategy){
		strategies.replace(type, strategy);
	}
	public void init(){
		_14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_CopositeStrategy temp = new _14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_CopositeStrategy();
		temp.setInfor("Discount001|Discount003");
		strategies.put(2, new _14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_FlatRateStrategy(1));
		strategies.put(3, new _14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_PercentageStrategy(7));
		strategies.put(1, new _14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_PercentageStrategy(3));
		temp.add(strategies.get(1));
		temp.add(strategies.get(2));
		strategies.put(4, temp);
		strategy.add(new _14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_StrategySpecification(2,"¾ø¶ÔÖµÓÅ»İ²ßÂÔ1","Discount001","¾ø¶ÔÖµÓÅ»İ²ßÂÔ"));
		strategy.add(new _14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_StrategySpecification(3,"°Ù·Ö±ÈÕÛ¿Û²ßÂÔ1","Discount002","°Ù·Ö±ÈÕÛ¿Û²ßÂÔ"));
		strategy.add(new _14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_StrategySpecification(1,"°Ù·Ö±ÈÕÛ¿Û²ßÂÔ2","Discount003","°Ù·Ö±ÈÕÛ¿Û²ßÂÔ"));
		strategy.add(new _14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_StrategySpecification(4,"¹Ë¿Í×îÓÅ²ßÂÔ","Discount004","×éºÏ²ßÂÔ"));
	}
	public ArrayList<_14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_StrategySpecification> getStrategySpecification(){
		return strategy;
	}
}
