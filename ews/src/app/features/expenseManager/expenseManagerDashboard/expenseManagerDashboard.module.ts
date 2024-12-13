import { CommonModule } from '@angular/common';
import { NgModule } from '@angular/core';
import { TranslateModule } from "@ngx-translate/core";
import { ExpenseManagerDashboardRoutingModule } from './expenseManagerDashboard.routing.module';
import { CardModule } from '@patterns/card';
import { ExpenseManagerDashboardComponent } from './expenseManagerDashboard.component';

@NgModule({
  declarations: [ExpenseManagerDashboardComponent],
  imports: [
    CardModule,
    CommonModule,
    TranslateModule,
    ExpenseManagerDashboardRoutingModule
  ],
  exports: [ExpenseManagerDashboardComponent],
})
export class ExpenseManagerDashboardModule {}