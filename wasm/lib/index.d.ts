declare namespace RuntimeExports {
	/**
	 * @param {string|null=} returnType
	 * @param {Array=} argTypes
	 * @param {Arguments|Array=} args
	 * @param {Object=} opts
	 */
	function ccall(ident: any, returnType?: (string | null) | undefined, argTypes?: any[] | undefined, args?: (Arguments | any[]) | undefined, opts?: any | undefined): any;
	/**
	 * @param {string=} returnType
	 * @param {Array=} argTypes
	 * @param {Object=} opts
	 */
	function cwrap(ident: any, returnType?: string | undefined, argTypes?: any[] | undefined, opts?: any | undefined): any;
	let HEAPF32: any;
	let HEAPF64: any;
	let HEAP_DATA_VIEW: any;
	let HEAP8: any;
	let HEAPU8: any;
	let HEAP16: any;
	let HEAPU16: any;
	let HEAP32: any;
	let HEAPU32: any;
	let HEAP64: any;
	let HEAPU64: any;
}
export interface WasmModule {
	_yespower_wasm(_0: number, _1: number, _2: number, _3: number, _4: number, _5: number): number;
	_malloc(_0: number): number;
	_free(_0: number): void;
}
export type MainModule = WasmModule & typeof RuntimeExports;
export declare function bytesToBase64(bytes: Uint8Array): string;
export declare function base64ToBytes(base64: string): Uint8Array<ArrayBuffer>;
export declare function bytesToHex(bytes: Uint8Array): string;
export declare function hexToBytes(hexStr: string): Uint8Array<ArrayBuffer>;
export type yespower_wasm = (input: number, inputLen: number, N: number, r: number, pers: string, persLen: number) => number;
export declare class Yespower {
	nByte: number;
	Module: MainModule;
	yespower_wasm: yespower_wasm;
	constructor(Module: MainModule);
	static init(): Promise<Yespower>;
	arrayToPtr(array: Uint8Array): number;
	ptrToArray(ptr: number, length: number): Uint8Array;
	freePtr(ptr: number): void;
	Hash(input: Uint8Array, N?: number, r?: number, pers?: string): Uint8Array;
}

export {};
