import { createRequire } from 'node:module';
const require = createRequire(import.meta.url);
const addon = require('./build/Release/yespower.node');

export const yespower = addon.yespower;