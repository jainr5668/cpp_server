import { CommonModule } from '@angular/common';
import { NgModule } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { ElementModule } from '@patterns/element';
import { ContentComponent } from './content.component';
import { MatGridListModule } from '@angular/material/grid-list'; 
@NgModule({
  declarations: [ContentComponent],
  imports: [CommonModule, ElementModule, FormsModule, MatGridListModule],
  exports: [ContentComponent],
})
export class ContentModule {}