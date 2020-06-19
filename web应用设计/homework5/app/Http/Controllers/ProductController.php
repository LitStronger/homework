<?php

namespace App\Http\Controllers;

use App\Product;
use Illuminate\Http\Request;
use JWTAuth;

class ProductController extends Controller
{

	public function store(Request $request)
	{
	    $this->validate($request, [
	        'name' => 'required',
	        'price' => 'required|integer',
	        'quantity' => 'required|integer'
	    ]);

	    $product = new Product();
	    $product->name = $request->name;
	    $product->price = $request->price;
	    $product->quantity = $request->quantity;

	    $product->save();
	    return response()->json([
	        'success' => true,
	        'product' => $product
	    ]);
	}


	public function destroy($id)
	{
        $product = new Product();
        $product = $product->where(['id' => $id])->first();
	    if (is_null($product)) {
	        return response()->json([
	            'success' => false,
	            'message' => 'Sorry, product with id ' . $id . ' cannot be found'
	        ], 400);
	    }

	   $product->delete(); 
	    return response()->json([
	        'message' => 'delete successfully'
        ]);	   
	}


	public function update(Request $request, $id)
	{
		$product = new Product();
        $product = $product->where(['id' => $id])->first();

	    if (is_null($product)) {
	        return response()->json([
	            'success' => false,
	            'message' => 'Sorry, product with id ' . $id . ' cannot be found'
	        ], 400);
	    }

	    $updated = $product->fill($request->all())->save();

	    if ($updated) {
	        return response()->json([
	            'message' => 'updated successfully'
	        ]);
	    } else {
	        return response()->json([
	            'success' => false,
	            'message' => 'Sorry, product could not be updated'
	        ], 500);
	    }
	}


	public function show($id)
	{
		$product = new Product();
        $product = $product->where(['id' => $id])->first();

	    if (is_null($product)) {
	        return response()->json([
	            'success' => false,
	            'message' => 'Sorry, product with id ' . $id . ' cannot be found'
	        ], 400);
	    }

	    return $product;
	}


	public function index()
	{
		$product = new Product();
	    return $product->all();
	}

}
