import { CommonModule } from '@angular/common';
import { NgModule } from '@angular/core';
import { TranslateModule } from "@ngx-translate/core";
import { SummaryCardComponent } from './summaryCard.component';

@NgModule({
  declarations: [SummaryCardComponent],
  imports: [
    CommonModule,
    TranslateModule,
  ],
  exports: [SummaryCardComponent],
})
export class SummaryCardModule {}