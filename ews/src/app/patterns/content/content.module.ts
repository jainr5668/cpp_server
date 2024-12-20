import { CommonModule } from '@angular/common';
import { NgModule } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { ElementModule } from '@patterns/element';
import { ContentComponent } from './content.component';
import { MatGridListModule } from '@angular/material/grid-list'; 
import { SummaryCardModule } from '@patterns/summaryCard';
@NgModule({
  declarations: [ContentComponent],
  imports: [CommonModule, ElementModule, FormsModule, MatGridListModule, SummaryCardModule],
  exports: [ContentComponent],
})
export class ContentModule {}