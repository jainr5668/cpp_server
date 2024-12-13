import { CommonModule } from '@angular/common';
import { NgModule } from '@angular/core';
import { TranslateModule } from "@ngx-translate/core";
import { ExpenseManagerRoutingModule } from './expenseManager.routing.module';
import { CardModule } from '@patterns/card';
import { ExpenseManagerComponent } from './expenseManager.component';

@NgModule({
  declarations: [ExpenseManagerComponent],
  imports: [
    CardModule,
    CommonModule,
    TranslateModule,
    ExpenseManagerRoutingModule,
  ],
  exports: [ExpenseManagerComponent],
})
export class ExpenseManagerModule { }