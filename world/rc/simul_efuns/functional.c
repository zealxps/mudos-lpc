
// functional for array
bool array_any(mixed *arr, fun callback, mixed *args...)
{
	foreach(mixed x in arr) {
		if (evaluate(callback, x, args...)) return true
	}
	return false
}

bool array_all(mixed *arr, fun callback, mixed *args...)
{
	foreach(mixed x in arr) {
		if (not evaluate(callback, x, args...)) return false
	}
	return true
}

mixed array_foldl(mixed *arr, mixed initVal, fun callback)
{
	foreach(mixed a in arr) {
		initVal = callback(a, initVal)
	}
	return initVal
}

mixed array_foldr(mixed *arr, mixed initVal, fun callback)
{
	for(int i = 0; i < sizeof(arr); i++) {
		initVal = callback(arr[sizeof(arr) - i -1], initVal)
	}
	return initVal
}

// generate functional
mixed any(mixed list, fun callback, mixed *args...)
{
	if (arrayp(list)) return array_any(list, callback, args...)
	else if (mapp(list)) {
		foreach(mixed key, mixed val in list) {
			if (callback(key, val)) return true
		}
		return false
	}
}

mixed all(mixed list, fun callback, mixed *args...)
{
	if (arrayp(list)) return array_all(list, callback, args...)
	else if(mapp(list)) {
		foreach(mixed key, mixed val in list) {
			if (not callback(key, val)) return false
		}
		return true
	}
}

// 想当于reduce，不过是自己设置初始值
mixed foldl(mixed list, mixed initVal, fun callback)
{
	if (arrayp(list)) return array_foldl(list, initVal, callback)
}

mixed foldr(mixed list, mixed initVal, fun callback)
{
	if (arrayp(list)) return array_foldr(list, initVal, callback)
}

mixed filter(mixed list, fun callback)
{
	if (arrayp(list)) return filter_array(list, callback)
}

mixed map(mixed list, fun callback)
{
	if (arrayp(list)) return map_array(list, callback)
	else if(mapp(list)) return map_mapping(list, callback)
}

mixed sort(mixed list, fun callback)
{
	if (arrayp(list)) return sort_array(list, callback)
}

void forall(mixed list, fun callback)
{
	if (arrayp(list)) {
		foreach (mixed val in list) {
			callback(val)
		}
	} else if (mapp(list)) {
		foreach (mixed key, mixed val in list) {
			callback(key, val)
		}
	}
}

mixed add(mixed x, mixed y) -> x + y 
mixed sub(mixed x, mixed y) -> x - y 
// littler
bool lt(mixed x, mixed y) -> x < y 
// greater
bool gt(mixed x, mixed y) -> x > y 
// zipMap
mapping zipMap(mixed *keys, mixed *values) 
{
	int size = sizeof(keys) < sizeof(values) ? sizeof(keys) : sizeof(values);
	mapping result_map = {};
	for (int i=0; i<size; i++) {
		result_map[keys[i]] = values[i];
	}
	return result_map;

}

int *range(int start, int stop, int step)
{
	step = to_int(step);
	if (step == 0) {
		throw("step must not be zero");
	}
	int i;
	int *ret = [];
	if (step > 0) {
		for (i = start; i < stop; i += step) {
			ret += [i];
		}
	}
	else {
		for (i = start; i > stop; i += step) {
			ret += [i];
		}
	}
	return ret;
}

mapping counter(mixed *values)
{
	mapping result = {};
	foreach(mixed val in values){
		if (undefinedp(result[val])){
			result[val] = 1;
		}else{
			result[val] += 1;
		}
	}
	return result;
}
/*
 void test_counter()
{
	mixed *a = [1,1,2,2,2,5,7];
	//debug_message("count:%O", counter(a));
}

output:
module/school/rank.c  67:count:{
  1:2,
  2:3,
  5:1,
  7:1,
}
 */
